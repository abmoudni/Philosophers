/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <abmoudni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:17:35 by abmoudni          #+#    #+#             */
/*   Updated: 2026/02/27 07:17:48 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	params = (t_params){0};
	philos = NULL;
	if (!parse_args(argc, argv, &params))
	{
		printf("Usage: ");
		printf("./philo nbr_philo time_die time_eat time_sleep [nbr_meals]\n");
		return (1);
	}
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
