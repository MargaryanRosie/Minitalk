
// // struct sigaction {
// //     void (*sa_handler)(int);
// //     void (*sa_sigaction)(int, siginfo_t *, void *)
// //     sigset_t sa_mask;             
// //     int sa_flags;          
// // };

#include "minitalk.h"
#include <signal.h>

static void	signal_handler(int signal_number, siginfo_t *info, void *context)                      //info is needed so that if there are several clients sending messages, the bits will not be mixed together
{
	static int		counter = 8;
	static char		c = 0;
	static pid_t	client_pid = 0;

	(void)context;
	if (info->si_pid != client_pid)
	{
		client_pid = info->si_pid;
		counter = 8;
		c = 0;
	}
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
	if (counter == 0)
	{
		if (c == '\0')
			client_pid = 0;
		else
			write(1, &c, 1);
		counter = 8;
		c = 0;
	}
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
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;                                  //so that the handler will receive additional info about the flag
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
