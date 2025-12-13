
#include "philo.h"

int	parse_args(int argc, char **argv, t_params *params)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_valid_number(argv[i]))
			return (1);
		i++;
	}
	params->num_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->num_philos <= 0 || params->time_to_die <= 0 || params->time_to_eat <= 0 || params->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		params->must_eat_count = ft_atoi(argv[5]);
		if (params->must_eat_count <= 0)
			return (1);
	}
	else
		params->must_eat_count = -1;
	params->someone_died = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	t_params	params;
	t_philo		*philos;
	pthread_t	monitor;

	params = {0};
	philos = NULL;
	if (parse_args(argc, argv, &params))
	{
		printf("Usage: ");
		printf("./philo num_philos die_time eat_time sleep_time [must_eat]\n");
		return (1);
	}
	if (init_params(&params) || init_philos(&params, &philos))
	{
		destroy_philos(philos, params.num_philos);
		destroy_params(&params);
		return (1);
	}
	if (start_threads(&params, philos))
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < params.num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	destroy_philos(philos, params.num_philos);
	destroy_params(&params);
	return (0);
}
