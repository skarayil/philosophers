/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:52:48 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 09:04:42 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static bool	ft_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start = ft_gettime();
	i = -1;
	while (++i < data->args.philos)
	{
		data->philos[i].last_eat = data->start;
		if (pthread_create(&data->philos[i].thread, NULL, &ft_routine,
				&data->philos[i]) != 0)
			return (ft_error("Failed to create philosopher thread"));
	}
	if (pthread_create(&monitor, NULL, &ft_monitor, data) != 0)
		return (ft_error("Failed to create monitor thread"));
	i = -1;
	while (++i < data->args.philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (true);
}

static void	ft_cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args.philos)
		pthread_mutex_destroy(&data->mtx.forks[i]);
	pthread_mutex_destroy(&data->mtx.write);
	pthread_mutex_destroy(&data->mtx.dead);
	pthread_mutex_destroy(&data->mtx.meal);
	free(data->philos);
	free(data->mtx.forks);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		ft_error("Usage: ./philo number die eat sleep limit");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_init(&data, av))
		return (1);
	if (!ft_simulation(&data))
	{
		ft_cleanup(&data);
		return (1);
	}
	ft_cleanup(&data);
	return (0);
}
