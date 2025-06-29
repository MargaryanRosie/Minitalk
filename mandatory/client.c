#include "../minitalk.h"

int	g_ack_received = 0;

void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		//write(1, "Server received the message\n", 28);
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGUSR1)
	{
		//write(1, "Bit received\n", 13);
		g_ack_received = 1;
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
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
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
	while (1)
		pause();
	return (0);
}
