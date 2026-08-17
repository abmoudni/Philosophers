/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:16:45 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:16:46 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->params->num_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->params->forks[left]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->params->forks[right]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->params->forks[right]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->params->forks[left]);
		print_action(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_time_mtx);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal_time_mtx);
	ft_usleep(philo->params, philo->params->time_to_eat);
	pthread_mutex_lock(&philo->meals_eat_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eat_mtx);
}

void	release_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->params->num_philos;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->params->forks[left]);
		pthread_mutex_unlock(&philo->params->forks[right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->params->forks[right]);
		pthread_mutex_unlock(&philo->params->forks[left]);
	}
}

void	go_to_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->params, philo->params->time_to_sleep);
}

void	think(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	print_action(philo, "is thinking");
	if (params->num_philos % 2
		&& params->time_to_eat >= params->time_to_sleep - 10)
		ft_usleep(params, params->time_to_eat - params->time_to_sleep + 10);
}
