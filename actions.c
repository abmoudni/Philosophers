
#include "philo.h"

void print_action(t_philo *philo, char *msg) {
    pthread_mutex_lock(&philo->params->someone_died_mtx);
    pthread_mutex_lock(&philo->params->print_lock);
    if (!philo->params->someone_died)
        printf("%ld %d %s\n", get_time_ms() - philo->params->start_time,
            philo->id + 1, msg);
    pthread_mutex_unlock(&philo->params->print_lock);//happened deadlock in this function
    pthread_mutex_unlock(&philo->params->someone_died_mtx);
    }

//     void print_action(t_philo *philo, char *msg)
// {
//     // 1) نقرأ حالة someone_died بشكل منفصل
//     pthread_mutex_lock(&philo->params->someone_died_mtx);
//     if (philo->params->someone_died)
//     {
//         pthread_mutex_unlock(&philo->params->someone_died_mtx);
//         return ;
//     }
//     pthread_mutex_unlock(&philo->params->someone_died_mtx);

//     // 2) الآن فقط نقفل الطباعة وحدها
//     pthread_mutex_lock(&philo->params->print_lock);
//     printf("%ld %d %s\n",
//         get_time_ms() - philo->params->start_time,
//         philo->id + 1, msg);
//     pthread_mutex_unlock(&philo->params->print_lock);
// }

void take_forks(t_philo *philo) {
    int id = philo->id;
    int left = id;
    int right = (id + 1) % philo->params->num_philos;

    if (id % 2 == 0) {
        pthread_mutex_lock(&philo->params->forks[left]);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->params->forks[right]);
        print_action(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(&philo->params->forks[right]);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->params->forks[left]);
        print_action(philo, "has taken a fork");
    }
}

void release_forks(t_philo *philo) {
    if (philo->id % 2 == 0) {
        pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % philo->params->num_philos]);
        pthread_mutex_unlock(&philo->params->forks[philo->id]);
    } else {
        pthread_mutex_unlock(&philo->params->forks[philo->id]);
        pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % philo->params->num_philos]);
    }
}

void eat(t_philo *philo) {
    print_action(philo, "is eating");

    pthread_mutex_lock(&philo->last_meal_time_mtx);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->last_meal_time_mtx);

    pthread_mutex_lock(&philo->meals_eat_mtx);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meals_eat_mtx);

    ft_usleep(philo, philo->params->time_to_eat * 1000);
}

void go_to_sleep(t_philo *philo) {
    print_action(philo, "is sleeping");
    ft_usleep(philo, philo->params->time_to_sleep * 1000);
}

void think(t_philo *philo) {
    print_action(philo, "is thinking");
}
