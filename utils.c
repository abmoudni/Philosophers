/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:25:12 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:25:30 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_died(t_params *params)
{
	pthread_mutex_lock(&params->someone_died_mtx);
	if (params->someone_died)
	{
		pthread_mutex_unlock(&params->someone_died_mtx);
		return (1);
	}
	pthread_mutex_unlock(&params->someone_died_mtx);
	return (0);
}

void	print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->params->print_lock);
	if (is_someone_died(philo->params))
	{
		pthread_mutex_unlock(&philo->params->print_lock);
		return ;
	}
	printf("%ld %d %s\n", get_time_ms()
		- philo->params->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->params->print_lock);
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
	int	res;

	res = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (INT_MAX / 10 < res || INT_MAX - res * 10 < (str[i] - 48))
			return (-1);
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}

void	ft_usleep(t_params *params, long time)
{
	long		curr_time;

	curr_time = get_time_ms();
	while (!is_someone_died(params))
	{
		if (time <= get_time_ms() - curr_time)
			break ;
		usleep(50);
	}
}
