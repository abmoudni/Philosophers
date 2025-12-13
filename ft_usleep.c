
#include "philo.h"

void ft_usleep(t_philo *philo, unsigned long time) {
    
    t_params *params = philo->params;
    unsigned long curr_time = get_time_ms();

    while (1)
    {
        pthread_mutex_lock(&params->someone_died_mtx);
        if (params->someone_died || time <= 1000 * (get_time_ms() - curr_time)){
            pthread_mutex_unlock(&params->someone_died_mtx);
            break ;
        }
        pthread_mutex_unlock(&params->someone_died_mtx);
        usleep(50);
    }
}
