#include "../minitalk.h"
#include <signal.h>

static void	signal_handler(int signal_number, siginfo_t *info, void *context)                      //info is needed so that if there are several clients sending messages, the bits will not be mixed together
{
	static int					counter = 8;
	static pid_t				client_pid = 0;
	static unsigned char		c = 0;

	(void)context;
	if (!info)
		return ;
	if (client_pid != info->si_pid)
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
			kill(info->si_pid, SIGUSR2);
		write(1, &c, 1);
		counter = 8;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);            //acknowledgement for bit(when this signal is sent to the clent, ack becomes 1)
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
	act.sa_flags = SA_SIGINFO;                                  //so that the handler will receive additional info about the flag
	
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
