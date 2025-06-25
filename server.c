#include "minitalk.h"

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}