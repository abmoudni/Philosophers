/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:19:21 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:22:38 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	long	delta_time;

	pthread_mutex_lock(&philo->last_meal_time_mtx);
	delta_time = get_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_time_mtx);
	return (philo->params->time_to_die <= delta_time);
}

static void	report_died(t_params *params)
{
	pthread_mutex_lock(&params->someone_died_mtx);
	params->someone_died = 1;
	pthread_mutex_unlock(&params->someone_died_mtx);
}

static int	check_deaths(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philos)
	{
		if (check_death(&philos[i]))
		{
			pthread_mutex_lock(&philos->params->print_lock);
			report_died(philos[i].params);
			printf("%ld %d died\n", get_time_ms()
				- philos[i].params->start_time, philos[i].id + 1);
			pthread_mutex_unlock(&philos->params->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_ate_enough(t_philo *philos)
{
	int			i;
	t_params	*params;

	params = philos->params;
	if (params->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_lock(&philos[i].meals_eat_mtx);
		if (philos[i].meals_eaten < params->must_eat_count)
		{
			pthread_mutex_unlock(&philos[i].meals_eat_mtx);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meals_eat_mtx);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;

	philos = arg;
	while (1)
	{
		if (check_deaths(philos) || all_ate_enough(philos))
			break ;
		usleep(50);
	}
	report_died(philos->params);
	return (NULL);
}
