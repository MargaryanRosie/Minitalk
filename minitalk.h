#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int		ft_atoi(char *str);
int		is_digit(char c);
void	ft_putnbr(int num);
void	ack_handler(int sig);
void	check_arguments(int argc, char *argv[]);
int		check_server_pid(pid_t server_pid);

#endif