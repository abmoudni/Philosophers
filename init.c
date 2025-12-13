
#include "philo.h"

int init_params(t_params *params) {
    int i;

    params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
    if (!params->forks)
        return (1);
    memset(params->forks, 0, sizeof(pthread_mutex_t) * params->num_philos);
    i = 0;
    while (i < params->num_philos) {
        if (pthread_mutex_init(&params->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&params->someone_died_mtx, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&params->print_lock, NULL) != 0)
        return (1);
    return (0);
}

int init_philos(t_params *params, t_philo **philos) {
    int i = 0;
    t_philo *philo;
    *philos = malloc(sizeof(t_philo) * params->num_philos);
    if (!*philos)
        return (1);
    memset(*philos, 0, sizeof(t_philo) * params->num_philos);
    while (i < params->num_philos) {
        philo = (*philos)[i];
        philo->id = i;
        philo->meals_eaten = 0;
        philo->params = params;
        if (pthread_mutex_init(&philo->meals_eat_mtx, NULL) != 0)
            return (1);
        if (pthread_mutex_init(&philo->last_meal_time_mtx, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

int start_threads(t_params *params, t_philo *philos) {
    int i;

    params->start_time = get_time_ms();
    i = 0;
    while (i < params->num_philos)
    {
        philos[i].last_meal_time = params->start_time;
        pthread_create(&philos[i].thread, NULL, philosopher_thread, &philos[i])
        i++;
    }
    return (0);
}
