
#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	params = (t_params){0};
	if (!parse_args(argc, argv, &params))
	{
		printf("Usage: ");
		printf("./philo nbr_philo time_die time_eat time_sleep [nbr_meals]\n");
		return (1);
	}
	philos = NULL;
	if (!init_params(&params) || !init_philos(&philos, &params))
	{
		destroy_philos(philos, params.num_philos);
		destroy_params(&params);
		return (1);
	}
	start(philos, &params);
	destroy_philos(philos, params.num_philos);
	destroy_params(&params);
	return (0);
}
