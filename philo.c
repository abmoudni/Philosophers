
#include "philo.h"

static void	*philo_one(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(&params->forks[0]);
	print_action(philo, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&params->someone_died_mtx);
		if (params->someone_died)
			break ;
		pthread_mutex_unlock(&params->someone_died_mtx);
		ft_usleep(philo, params->time_to_die * 1000);
	}
	pthread_mutex_unlock(&params->someone_died_mtx);
	pthread_mutex_unlock(&params->forks[0]);
	return (NULL);
}

void	*philos_routine(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = arg;
	params = philo->params;
	if (params->num_philos == 1)
		return (philo_one(philo));
	if (philo->id % 2)
		usleep(1000);
	while (!is_someone_died(params))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		go_to_sleep(philo);
		think(philo);
	}
	return (NULL);
}
