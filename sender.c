#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int	ft_atoi(char *str);

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = getpid();
	printf("PID: %d\n", pid);
	kill(ft_atoi(argv[1]), SIGUSR1);     //uxarkum em es signaly 10579 pid unecox processin
	return 0;
}