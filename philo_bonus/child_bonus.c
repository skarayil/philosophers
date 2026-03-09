/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 03:11:52 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_and_start_monitor(t_philo *philo, t_local *local, t_data *data)
{
	pthread_t	monitor;

	local->id = philo->id;
	local->last_meal = data->start_time;
	local->eat_count = 0;
	local->data = data;
	pthread_create(&monitor, NULL, monitor_thread, local);
	pthread_detach(monitor);
}

static void	handle_single_philo(t_philo *philo, t_data *data)
{
	sem_wait(data->sem.forks);
	ft_write(philo, MSG_TAKE_FORK);
	ft_usleep(data->args.die + 10);
	sem_post(data->sem.forks);
	free(data->philos);
	exit(0);
}

static void	philo_loop(t_local *local, t_data *data)
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

static void	cleanup_and_exit(t_local *local, t_data *data)
{
	sem_close(local->meal_lock);
	free(data->philos);
	exit(0);
}

void	ft_child_routine(t_philo *philo)
{
	t_data	*data;
	t_local	local;
	char	sem_name[256];

	data = philo->data;
	init_and_start_monitor(philo, &local, data);
	create_meal_semaphore(&local, sem_name, data);
	if (data->args.philos == 1)
		handle_single_philo(philo, data);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo_loop(&local, data);
	cleanup_and_exit(&local, data);
}
