/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:43:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/27 16:32:12 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_eat(t_philo *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
	ft_write(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(f2);
	ft_write(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(&philo->data->mtx.meal);
	philo->last_eat = ft_gettime();
	philo->time_eat++;
	pthread_mutex_unlock(&philo->data->mtx.meal);
	ft_write(philo, MSG_EATING);
	if (!ft_usleep(philo->data->args.eat, philo->data))
	{
		pthread_mutex_unlock(f2);
		pthread_mutex_unlock(f1);
		return (false);
	}
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
	return (true);
}

static bool	ft_sleep(t_philo *philo)
{
	ft_write(philo, MSG_SLEEPING);
	return (ft_usleep(philo->data->args.sleep, philo->data));
}

static bool	ft_think(t_philo *philo)
{
	long	time;

	ft_write(philo, MSG_THINKING);
	if (philo->data->args.philos % 2 != 0)
	{
		time = (philo->data->args.eat * 2) - philo->data->args.sleep;
		if (time > 0)
			return (ft_usleep(time, philo->data));
	}
	return (ft_usleep(1, philo->data));
}

static bool	ft_run(t_philo *philo)
{
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;

	if (philo->port < philo->star)
	{
		f1 = philo->port;
		f2 = philo->star;
	}
	else
	{
		f1 = philo->star;
		f2 = philo->port;
	}
	while (true)
	{
		if (!ft_eat(philo, f1, f2) || !ft_sleep(philo) || !ft_think(philo))
			return (false);
	}
	return (true);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->args.philos == 1)
	{
		pthread_mutex_lock(philo->port);
		ft_write(philo, MSG_TAKE_FORK);
		ft_usleep(philo->data->args.die, philo->data);
		pthread_mutex_unlock(philo->port);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->args.eat / 2, philo->data);
	ft_run(philo);
	return (NULL);
}
