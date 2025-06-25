#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		write(1, "Hello\n", 6);
	}
}
int	main()
{
	pid_t pid;
	
	pid = getpid();
	printf("PID: %d\n", pid);
	signal(SIGUSR1, signal_handler);              //if i will receive signal SIGUSR1, do the function signal_handler
	//if i dont write pause(), as there is no other code, the program will exit immediately, so i nned to enter an infinite loop
	while (1)
		pause();
	return 0;
}