/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/15 10:07:20 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_start(t_philo *philo, t_local *local, t_data *data)
{
	pthread_t	monitor;

	local->id = philo->id;
	local->last_eat = data->start;
	local->time_eat = 0;
	local->data = data;
	pthread_create(&monitor, NULL, ft_monitor, local);
	pthread_detach(monitor);
}

static void	ft_single(t_philo *philo, t_data *data)
{
	sem_wait(data->sem.forks);
	ft_write(philo, MSG_TAKE_FORK);
	ft_usleep(data->args.die + 10);
	sem_post(data->sem.forks);
	free(data->philos);
	exit(0);
}

static void	ft_loop(t_local *local, t_data *data)
{
	while (42)
	{
		ft_eat(local, data);
		sem_wait(local->lock);
		if (data->args.limit != -1 && local->time_eat >= data->args.limit)
		{
			sem_post(local->lock);
			break ;
		}
		sem_post(local->lock);
		ft_sleep_think(local, data);
	}
}

static void	ft_exit(t_local *local, t_data *data)
{
	sem_close(local->lock);
	free(data->philos);
	exit(0);
}

void	ft_child(t_philo *philo)
{
	t_data	*data;
	t_local	local;
	char	name[256];

	data = philo->data;
	ft_start(philo, &local, data);
	ft_meal(&local, name, data);
	if (data->args.philos == 1)
		ft_single(philo, data);
	if (philo->id % 2 == 0)
		usleep(1000);
	ft_loop(&local, data);
	ft_exit(&local, data);
}
