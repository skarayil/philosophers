/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:52:21 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/27 16:26:05 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

bool	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
	{
		pthread_mutex_lock(&data->mtx.dead);
		if (!data->alive)
		{
			pthread_mutex_unlock(&data->mtx.dead);
			return (false);
		}
		pthread_mutex_unlock(&data->mtx.dead);
		if (data->args.philos < 50)
			usleep(100);
		else
			usleep(500);
	}
	return (true);
}
