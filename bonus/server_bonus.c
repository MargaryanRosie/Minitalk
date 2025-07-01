/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romargar <romargar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:48:33 by romargar          #+#    #+#             */
/*   Updated: 2025/07/01 14:11:13 by romargar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"
#include <signal.h>

static void	check_interrupt(pid_t *pid, int *counter, char *c, siginfo_t *info)
{
	if (*pid != info->si_pid)
	{
		*pid = info->si_pid;
		*counter = 8;
		*c = 0;
	}
}

static void	output_char(char *c, int *counter, pid_t pid)
{
	if (*counter == 0)
	{
		if (*c == '\0')
			kill(pid, SIGUSR2);
		write(1, c, 1);
		*counter = 8;
		*c = 0;
	}
}

static void	signal_handler(int signal_number, siginfo_t *info, void *context)
{
	static int		counter = 8;
	static pid_t	client_pid = 0;
	static char		c = 0;

	(void)context;
	check_interrupt(&client_pid, &counter, &c, info);
	if (signal_number == SIGUSR1)
	{
		if (counter > 0)
			counter--;
	}
	else if (signal_number == SIGUSR2)
	{
		if (counter > 0)
		{
			c = c | (1 << (counter - 1));
			counter--;
		}
	}
	output_char(&c, &counter, client_pid);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	act;

	server_pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
