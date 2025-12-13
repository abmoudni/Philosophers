
#include "philo.h"

int destroy_params(t_params *params)
{
	int	i;

	if (!params->forks)
		return (0);
    i = 0;
    while (i < params->num_philos && params->forks[i])
	{
	    pthread_mutex_destroy(&params->forks[i]);
        i++;
    }
	free(params->forks);
	if (params->someone_died_mtx)
	    pthread_mutex_destroy(&params->someone_died_mtx);
	if (params->print_lock)
	    pthread_mutex_destroy(&params->print_lock);
	return (0);
}

int destroy_philos(t_philo *philos, int num_philos)
{
	int		i;
	t_philo	*philo;

	if (!philos)
		return (0);
	i = 0;
	while (i < num_philos)
	{
		philo = &philos[i];
		if (philo->meals_eat_mtx)
    	    pthread_mutex_destroy(philo->meals_eat_mtx);
		if (philo->last_meal_time_mtx)
	        pthread_mutex_destroy(philo->last_meal_time_mtx);
		i++;
	}
	free(philos);
}
