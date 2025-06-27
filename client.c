// struct sigaction {
//     void (*sa_handler)(int); // Pointer to the handler function
//     sigset_t sa_mask;        // set of signals to be blocked(if the handler is still running, this blocks other signals so that they dont interrupt the handler function)
//     int sa_flags;            // Flags for additional behaviour, for example give additional info about the sender when the signal is sent or restart interrupted system calls
// };


#include "minitalk.h"

static void	check_arguments(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		write(2, "Invalid number of arguments.\n", 29);
		exit(8);
	}
	i = 0;
	while (argv[1][i])
	{
		if (is_digit(argv[1][i]))
			i++;
		else 
		{
			write(2, "Invalid server PID.\n", 20);
			exit(2);
		}
	}
	if (argv[2][0] == '\0')
	{
		write(2, "Empty message.\n", 15);
		exit(3);
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
		exit(4);
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
                exit(5);
		}
		else if (bit == 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
                exit(6);
		}
		i--;
		usleep(800);
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
	send_message(message, server_pid);
	return (0);
}
