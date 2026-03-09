/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:58:17 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/27 16:32:38 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	ft_parser(t_data *data, char *av[])
{
	data->args.philos = ft_atoi(av[1]);
	data->args.die = ft_atoi(av[2]);
	data->args.eat = ft_atoi(av[3]);
	data->args.sleep = ft_atoi(av[4]);
	if (av[5])
		data->args.limit = ft_atoi(av[5]);
	else
		data->args.limit = -1;
}

static bool	ft_malloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->args.philos);
	if (!data->philos)
		return (ft_error("Memory allocation failed for philosophers"));
	data->mtx.forks = malloc(sizeof(pthread_mutex_t) * data->args.philos);
	if (!data->mtx.forks)
	{
		free(data->philos);
		return (ft_error("Memory allocation failed for forks"));
	}
	return (true);
}

static bool	ft_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->mtx.write, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->mtx.dead, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->mtx.meal, NULL) != 0)
		return (false);
	i = -1;
	while (++i < data->args.philos)
		if (pthread_mutex_init(&data->mtx.forks[i], NULL) != 0)
			return (false);
	return (true);
}

static void	ft_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args.philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_eat = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		data->philos[i].port = &data->mtx.forks[i];
		data->philos[i].star = &data->mtx.forks[(i + 1) % data->args.philos];
	}
}

bool	ft_init(t_data *data, char *av[])
{
	ft_parser(data, av);
	if (data->args.philos <= 0 || data->args.die <= 0 || data->args.eat <= 0
		|| data->args.sleep <= 0 || (av[5] && data->args.limit <= 0))
		return (ft_error("All values must be positive integers"));
	if (!ft_malloc(data))
		return (false);
	if (!ft_mutex(data))
	{
		free(data->philos);
		free(data->mtx.forks);
		return (false);
	}
	ft_philos(data);
	data->alive = true;
	data->start = 0;
	return (true);
}
