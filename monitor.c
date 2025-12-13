#include "philo.h"

int check_death(t_philo *philos, int i) {
    pthread_mutex_lock(&philos[i].last_meal_time_mtx);
    if (get_time_ms() - philos[i].last_meal_time >= philos[i].params->time_to_die) {

        pthread_mutex_lock(&philos[i].params->someone_died_mtx);
        if (!philos[i].params->someone_died) {

            pthread_mutex_lock(&philos[i].params->print_lock); //?
            printf("%ld %d died\n", get_time_ms() - philos[i].params->start_time, philos[i].id + 1);
            pthread_mutex_unlock(&philos[i].params->print_lock);
            
            philos[i].params->someone_died = 1;
        }
        pthread_mutex_unlock(&philos[i].params->someone_died_mtx);
        pthread_mutex_unlock(&philos[i].last_meal_time_mtx);
        return (1);
    }

    pthread_mutex_unlock(&philos[i].last_meal_time_mtx);
    return (0);
}

int all_ate_enough(t_philo *philos, t_params *params) {
    int i = 0;
    if (params->must_eat_count == -1)
    {
        return (0);
    }
    while (i < params->num_philos) {
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

void *monitor_routine(void *arg) {
    t_philo *philos = (t_philo *)arg;
    t_params *params = philos[0].params;

    while (1) {
        int i = 0;
        while (i < params->num_philos) {
            if (check_death(philos, i))
                break;
            i++;
        }

        if (i != params->num_philos)
            break ;

        if (all_ate_enough(philos, params))
            break ;

        ft_usleep(philos, 1000);
    }
    pthread_mutex_lock(&params->someone_died_mtx);
    params->someone_died = 1;
    pthread_mutex_unlock(&params->someone_died_mtx);
    return NULL;
}
