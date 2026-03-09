/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:57:11 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/27 16:32:54 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static bool	ft_check(t_data *data, int i)
{
	long	curr;
	long	time;

	curr = ft_gettime();
	pthread_mutex_lock(&data->mtx.meal);
	time = curr - data->philos[i].last_eat;
	pthread_mutex_unlock(&data->mtx.meal);
	if (time >= data->args.die)
	{
		pthread_mutex_lock(&data->mtx.dead);
		if (data->alive)
		{
			data->alive = false;
			pthread_mutex_unlock(&data->mtx.dead);
			ft_write(&data->philos[i], MSG_DIED);
			return (true);
		}
		pthread_mutex_unlock(&data->mtx.dead);
		return (true);
	}
	return (false);
}

static bool	ft_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args.philos)
	{
		if (ft_check(data, i))
			return (true);
	}
	return (false);
}

static bool	ft_meals(t_data *data)
{
	int	i;
	int	ok;

	if (data->args.limit == -1)
		return (false);
	i = -1;
	ok = 0;
	while (++i < data->args.philos)
	{
		pthread_mutex_lock(&data->mtx.meal);
		if (data->philos[i].time_eat >= data->args.limit)
			ok++;
		pthread_mutex_unlock(&data->mtx.meal);
	}
	if (ok == data->args.philos)
	{
		pthread_mutex_lock(&data->mtx.dead);
		data->alive = false;
		pthread_mutex_unlock(&data->mtx.dead);
		ft_write(&data->philos[0], MSG_FINISHED);
		return (true);
	}
	return (false);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (true)
	{
		pthread_mutex_lock(&data->mtx.dead);
		if (!data->alive)
		{
			pthread_mutex_unlock(&data->mtx.dead);
			break ;
		}
		pthread_mutex_unlock(&data->mtx.dead);
		if (ft_death(data) || ft_meals(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
