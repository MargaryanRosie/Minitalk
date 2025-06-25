#include "../minitalk.h"
#include <limits.h>

void	ft_putnbr(int num)
{
	char	c;

	if (num == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 9)
		ft_putnbr(num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
}