
#include "philo.h"

int	init_params(t_params *params)
{
	int	i;

	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	if (!params->forks)
		return (0);
	memset(params->forks, 0, sizeof(pthread_mutex_t) * params->num_philos);
	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&params->someone_died_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&params->print_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_philos(t_philo **philos, t_params *params)
{
	int		i;
	t_philo	*p;

	*philos = malloc(sizeof(t_philo) * params->num_philos);
	if (!*philos)
		return (0);
	memset(*philos, 0, sizeof(t_philo) * params->num_philos);
	i = 0;
	while (i < params->num_philos)
	{
		p = (*philos) + i;
		p->id = i;
		p->meals_eaten = 0;
		p->params = params;
		if (pthread_mutex_init(&p->meals_eat_mtx, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&p->last_meal_time_mtx, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
