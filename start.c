/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:23:21 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:23:22 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_philos(t_philo *philos, t_params *params)
{
	int	i;

	i = 0;
	params->start_time = get_time_ms();
	while (i < params->num_philos)
	{
		philos[i].last_meal_time = params->start_time;
		pthread_create(&philos[i].thread, NULL, philos_routine, &philos[i]);
		i++;
	}
}

void	start(t_philo *philos, t_params *params)
{
	int			i;
	pthread_t	monitor;

	start_philos(philos, params);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
