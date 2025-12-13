#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <limit.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params {
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;

    long            start_time;
    int             someone_died;
    pthread_mutex_t someone_died_mtx;
    pthread_mutex_t print_lock;
    pthread_mutex_t *forks;
}   t_params;

typedef struct s_philo {
    int             id;
    int             meals_eaten;
    pthread_mutex_t meals_eat_mtx;
    long            last_meal_time;
    pthread_mutex_t last_meal_time_mtx;
    pthread_t       thread;
    t_params        *params;
}   t_philo;

void    print_action(t_philo *philo, char *msg);
void    take_forks(t_philo *philo);
void    release_forks(t_philo *philo);
void    eat(t_philo *philo);
void    go_to_sleep(t_philo *philo);
void    think(t_philo *philo);

int     init_mutexes(t_params *params);
int     init_philos(t_params *params, t_philo **philos);
int     start_threads(t_params *params, t_philo *philos);
int     destroy_mutexes(t_philo *philos);
void    ft_usleep(t_philo *philo, unsigned long time);
void    *monitor_routine(void *arg);
void    *philosopher_thread(void *arg);

// utils.c
int     ft_valid_number(char *str);
long    get_time_ms(void);
int     ft_atoi(const char *str);

#endif
