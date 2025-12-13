
#include "philo.h"

static int	check_death(t_philo *philo)
{
	long	delta_time;

	pthread_mutex_lock(&philo->last_meal_time_mtx);
	delta_time = get_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_time_mtx);
	return (philo->params->time_to_die <= delta_time);
}

static void	report_died(t_params *params, int id)
{
	pthread_mutex_lock(&params->someone_died_mtx);
	params->someone_died = 1;
	pthread_mutex_unlock(&params->someone_died_mtx);
	pthread_mutex_lock(&params->print_lock);
	printf("%ld %d died\n", get_time_ms() - params->start_time, id + 1);
	pthread_mutex_unlock(&params->print_lock);
}

static int	check_deaths(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philos)
	{
		if (check_death(&philos[i]))
		{
			report_died(philos[i].params, i);
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
	int			i;
	t_philo		*philos;
	t_params	*params;

	philos = arg;
	params = philos->params;
	while (1)
	{
		if (check_deaths(philos) || all_ate_enough(philos))
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&params->someone_died_mtx);
	params->someone_died = 1;
	pthread_mutex_unlock(&params->someone_died_mtx);
	return (NULL);
}
