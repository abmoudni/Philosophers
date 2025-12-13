#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_valid_number(char *str)
{
	int	i;

	if (*str == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sing;
	int	res;

	i = 0;
	sing = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sing = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		//? overflow
		if (INT_MAX / 10 < res || INT_MAX - res * 10 < (str[i] - 48))
			return (-1);
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sing);
}
