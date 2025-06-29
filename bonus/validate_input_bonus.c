#include "../minitalk.h"

void	check_arguments(int argc, char *argv[])
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
int	check_server_pid(pid_t server_pid)
{
	if (kill(server_pid, 0) == 0 && server_pid > 0)
		return (1);
	else
	{
		write(2, "Wrong PID.\n", 11);
		exit(EXIT_FAILURE);
	}
}