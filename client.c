#include "minitalk.h"

int	ack_received = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "Server received the message\n", 28);
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGUSR1)
	{
		write(1, "Bit received\n", 13);
		ack_received = 1;
	}
}

static void	check_arguments(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		write(2, "Invalid number of arguments.\n", 29);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv[1][i])
	{
		if (is_digit(argv[1][i]))
			i++;
		else 
		{
			write(2, "Invalid server PID.\n", 20);
			exit(EXIT_FAILURE);
		}
	}
	if (argv[2][0] == '\0')
	{
		write(2, "Empty message.\n", 15);
		exit(EXIT_FAILURE);
	}
}

//kill function returns 0 if sending the signal to the specified pid was successful
//valid process id is a positive number
//kill(pid, 0)   does not send any signal, it is used to check if the pid is valid
static int	check_server_pid(pid_t server_pid)
{
	if (kill(server_pid, 0) == 0 && server_pid > 0)
		return (1);
	else
	{
		write(2, "Wrong PID.\n", 11);
		exit(EXIT_FAILURE);
	}
}

static void	char_to_binary(char c, int server_pid)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
                exit(EXIT_FAILURE);
		}
		else if (bit == 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
                exit(EXIT_FAILURE);
		}
		i--;
		usleep(800);
		while (!ack_received)
			pause();
		ack_received = 0;
	}
}

static void	send_message(char *message, int server_pid)
{
	int		i;

	i = 0;
	while (message[i])
	{
		char_to_binary(message[i], server_pid);
		i++;
	}
	char_to_binary(message[i], server_pid);
}

int	main(int argc, char *argv[])
{
	char	*message;
	pid_t	server_pid;

	check_arguments(argc, argv);
	server_pid = ft_atoi(argv[1]);
	check_server_pid(server_pid);
	message = argv[2];
	signal(SIGUSR2, &ack_handler);
	signal(SIGUSR1, &ack_handler);
	send_message(message, server_pid);
	while(1)
		pause();
	return (0);
}
