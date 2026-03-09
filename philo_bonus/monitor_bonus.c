/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 09:50:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.philos)
	{
		kill(data->philos[i].pid, SIGTERM);
		i++;
	}
}

static int	ft_check(t_data *data, int *finished)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (pid <= 0)
		return (-1);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			return (1);
		else if (WEXITSTATUS(status) == 0)
		{
			(*finished)++;
			if (*finished == data->args.philos)
				return (2);
		}
	}
	return (0);
}

void	ft_parent(t_data *data)
{
	int	finished;
	int	ret;

	finished = 0;
	while (1)
	{
		ret = ft_check(data, &finished);
		if (ret == -1)
			break ;
		if (ret == 1)
		{
			ft_kill(data);
			while (waitpid(-1, NULL, 0) > 0)
				;
			break ;
		}
		if (ret == 2)
			break ;
	}
}

void	*ft_monitor(void *arg)
{
	t_local	*local;
	t_data	*data;
	long	elapsed;
	t_philo	tmp_philo;

	local = (t_local *)arg;
	data = local->data;
	while (1)
	{
		usleep(500);
		sem_wait(local->meal_lock);
		elapsed = ft_gettime() - local->last_meal;
		sem_post(local->meal_lock);
		if (elapsed >= data->args.die)
		{
			tmp_philo.id = local->id;
			tmp_philo.data = data;
			ft_write(&tmp_philo, MSG_DIED);
			free(data->philos);
			exit(1);
		}
	}
	return (NULL);
}
