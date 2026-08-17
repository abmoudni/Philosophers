/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:17:02 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:17:03 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_params(t_params *params)
{
	int	i;

	if (!params->forks)
		return ;
	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	free(params->forks);
	pthread_mutex_destroy(&params->someone_died_mtx);
	pthread_mutex_destroy(&params->print_lock);
}

void	destroy_philos(t_philo *philos, int num_philos)
{
	int		i;
	t_philo	*p;

	if (!philos)
		return ;
	i = 0;
	while (i < num_philos)
	{
		p = &philos[i];
		pthread_mutex_destroy(&p->meals_eat_mtx);
		pthread_mutex_destroy(&p->last_meal_time_mtx);
		i++;
	}
	free(philos);
}
