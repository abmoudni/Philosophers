
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
	pthread_mutex_lock(&philo->meals_eat_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eat_mtx);
	ft_usleep(philo->params, philo->params->time_to_eat * 1000);
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
		print_action(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->params->forks[right]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->params->forks[right]);
		print_action(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->params->forks[left]);
		print_action(philo, "has taken a fork");
	}
}

void	go_to_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->params, philo->params->time_to_sleep * 1000);
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
