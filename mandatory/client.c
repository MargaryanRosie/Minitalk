/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romargar <romargar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:47:50 by romargar          #+#    #+#             */
/*   Updated: 2025/07/01 13:47:51 by romargar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	g_ack_received = 0;

void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGUSR1)
	{
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
		while (!g_ack_received)
			usleep(100);
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
