/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/15 10:07:20 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_forks(t_local *philo, t_data *data)
{
	sem_wait(data->sem.turn);
	sem_wait(data->sem.forks);
	ft_write(philo->data->philos + (philo->id - 1), MSG_TAKE_FORK);
	sem_wait(data->sem.forks);
	ft_write(philo->data->philos + (philo->id - 1), MSG_TAKE_FORK);
	sem_post(data->sem.turn);
}

static void	ft_name(char *name, t_local *local)
{
	char	pid[12];
	char	id[12];

	name[0] = '/';
	name[1] = 'm';
	name[2] = 'e';
	name[3] = 'a';
	name[4] = 'l';
	name[5] = '_';
	name[6] = 'l';
	name[7] = 'o';
	name[8] = 'c';
	name[9] = 'k';
	name[10] = '_';
	name[11] = '\0';
	ft_itoa(getpid(), pid);
	ft_itoa(local->id, id);
	ft_strcat(name, pid);
	ft_strcat(name, "_");
	ft_strcat(name, id);
}

void	ft_eat(t_local *philo, t_data *data)
{
	ft_forks(philo, data);
	sem_wait(philo->lock);
	philo->last_eat = ft_gettime();
	philo->time_eat++;
	sem_post(philo->lock);
	ft_write(philo->data->philos + (philo->id - 1), MSG_EATING);
	ft_usleep(data->args.eat);
	sem_post(data->sem.forks);
	sem_post(data->sem.forks);
}

void	ft_sleep_think(t_local *philo, t_data *data)
{
	ft_write(philo->data->philos + (philo->id - 1), MSG_SLEEPING);
	ft_usleep(data->args.sleep);
	ft_write(philo->data->philos + (philo->id - 1), MSG_THINKING);
	if (data->args.philos % 2 != 0)
		ft_usleep(data->args.eat / 2);
	else
		usleep(500);
}

void	ft_meal(t_local *local, char *name, t_data *data)
{
	ft_name(name, local);
	sem_unlink(name);
	local->lock = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	if (local->lock == SEM_FAILED)
	{
		free(data->philos);
		exit(1);
	}
}
