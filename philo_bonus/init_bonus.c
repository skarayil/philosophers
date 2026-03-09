/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 03:39:12 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static bool	ft_create_semaphores(t_data *data)
{
	sem_unlink("/philo_forks");
	data->sem.forks = sem_open("/philo_forks", O_CREAT, 0644,
			data->args.philos);
	if (data->sem.forks == SEM_FAILED)
		return (ft_error("sem_open failed for forks"));
	sem_unlink("/philo_turn");
	data->sem.turn = sem_open("/philo_turn", O_CREAT, 0644, 1);
	if (data->sem.turn == SEM_FAILED)
		return (ft_error("sem_open failed for turn"));
	sem_unlink("/philo_write");
	data->sem.write = sem_open("/philo_write", O_CREAT, 0644, 1);
	if (data->sem.write == SEM_FAILED)
		return (ft_error("sem_open failed for write"));
	return (true);
}

static bool	ft_init_philos_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->args.philos);
	if (!data->philos)
		return (ft_error("malloc failed for philos"));
	i = 0;
	while (i < data->args.philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].pid = 0;
		i++;
	}
	return (true);
}

static bool	ft_create_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->args.philos)
	{
		pid = fork();
		if (pid == -1)
			return (ft_error("fork failed"));
		if (pid == 0)
			ft_child_routine(&data->philos[i]);
		else
			data->philos[i].pid = pid;
		i++;
	}
	return (true);
}

bool	ft_init(t_data *data, char *av[])
{
	ft_parser(data, av);
	if (data->args.philos <= 0 || data->args.die <= 0 || data->args.eat <= 0
		|| data->args.sleep <= 0 || (av[5] && data->args.limit <= 0))
		return (ft_error("All values must be positive integers"));
	if (!ft_create_semaphores(data))
		return (false);
	if (!ft_init_philos_data(data))
	{
		ft_cleanup(data);
		return (false);
	}
	data->start_time = ft_gettime();
	if (!ft_create_processes(data))
	{
		ft_cleanup(data);
		return (false);
	}
	return (true);
}
