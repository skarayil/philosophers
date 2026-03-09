/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 03:41:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_take_forks(t_local *philo, t_data *data)
{
	sem_wait(data->sem.turn);
	sem_wait(data->sem.forks);
	ft_write(philo->data->philos + (philo->id - 1), MSG_TAKE_FORK);
	sem_wait(data->sem.forks);
	ft_write(philo->data->philos + (philo->id - 1), MSG_TAKE_FORK);
	sem_post(data->sem.turn);
}

void	ft_eat(t_local *philo, t_data *data)
{
	ft_take_forks(philo, data);
	sem_wait(philo->meal_lock);
	philo->last_meal = ft_gettime();
	philo->eat_count++;
	sem_post(philo->meal_lock);
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

static void	build_sem_name(char *sem_name, t_local *local)
{
	char	pid_str[12];
	char	id_str[12];

	sem_name[0] = '/';
	sem_name[1] = 'm';
	sem_name[2] = 'e';
	sem_name[3] = 'a';
	sem_name[4] = 'l';
	sem_name[5] = '_';
	sem_name[6] = 'l';
	sem_name[7] = 'o';
	sem_name[8] = 'c';
	sem_name[9] = 'k';
	sem_name[10] = '_';
	sem_name[11] = '\0';
	ft_itoa_buf(getpid(), pid_str);
	ft_itoa_buf(local->id, id_str);
	ft_strcat_buf(sem_name, pid_str);
	ft_strcat_buf(sem_name, "_");
	ft_strcat_buf(sem_name, id_str);
}

void	create_meal_semaphore(t_local *local, char *sem_name, t_data *data)
{
	build_sem_name(sem_name, local);
	sem_unlink(sem_name);
	local->meal_lock = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	if (local->meal_lock == SEM_FAILED)
	{
		free(data->philos);
		exit(1);
	}
}
