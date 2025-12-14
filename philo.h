
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	someone_died_mtx;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_mutex_t	meals_eat_mtx;
	long			last_meal_time;
	pthread_mutex_t	last_meal_time_mtx;
	pthread_t		thread;
	t_params		*params;
}	t_philo;

// parse_args.c
int		parse_args(int argc, char **argv, t_params *params);

// init.c
int		init_params(t_params *params);
int		init_philos(t_philo **philos, t_params *params);

// start.c
void	start(t_philo *philos, t_params *params);

// destroy.c
void	destroy_params(t_params *params);
void	destroy_philos(t_philo *philos, int num_philos);

// philo.c
void	*philos_routine(void *arg);

// monitor.c
void	*monitor_routine(void *arg);

// actions.c
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
void	go_to_sleep(t_philo *philo);
void	think(t_philo *philo);

// utils.c
void	print_action(t_philo *philo, const char *msg);
int		is_someone_died(t_params *params);
long	get_time_ms(void);
int		ft_atoi(const char *str);
void	ft_usleep(t_params *params, long time);

#endif
