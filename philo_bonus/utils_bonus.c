/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/08 04:31:49 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

bool	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

long	ft_gettime(void)
{
	struct timeval	clock;

	if (gettimeofday(&clock, NULL) != 0)
		return (1);
	return ((clock.tv_sec * 1000) + (clock.tv_usec / 1000));
}

bool	ft_usleep(long ms)
{
	long	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
		usleep(500);
	return (true);
}

void	ft_cleanup(t_data *data)
{
	if (data->sem.forks != SEM_FAILED)
	{
		sem_close(data->sem.forks);
		sem_unlink("/philo_forks");
	}
	if (data->sem.turn != SEM_FAILED)
	{
		sem_close(data->sem.turn);
		sem_unlink("/philo_turn");
	}
	if (data->sem.write != SEM_FAILED)
	{
		sem_close(data->sem.write);
		sem_unlink("/philo_write");
	}
	if (data->philos)
		free(data->philos);
}
