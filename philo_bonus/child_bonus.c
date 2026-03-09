/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 09:54:51 by skarayil         ###   ########.fr       */
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
	local->last_meal = data->start_time;
	local->eat_count = 0;
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
	while (1)
	{
		ft_eat(local, data);
		sem_wait(local->meal_lock);
		if (data->args.limit != -1 && local->eat_count >= data->args.limit)
		{
			sem_post(local->meal_lock);
			break ;
		}
		sem_post(local->meal_lock);
		ft_sleep_think(local, data);
	}
}

static void	ft_exit(t_local *local, t_data *data)
{
	sem_close(local->meal_lock);
	free(data->philos);
	exit(0);
}

void	ft_child(t_philo *philo)
{
	t_data	*data;
	t_local	local;
	char	sem_name[256];

	data = philo->data;
	ft_start(philo, &local, data);
	ft_meal(&local, sem_name, data);
	if (data->args.philos == 1)
		ft_single(philo, data);
	if (philo->id % 2 == 0)
		usleep(1000);
	ft_loop(&local, data);
	ft_exit(&local, data);
}
