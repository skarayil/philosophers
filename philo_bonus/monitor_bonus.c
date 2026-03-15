/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/15 10:07:20 by skarayil         ###   ########.fr       */
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

	i = -1;
	while (++i < data->args.philos)
		kill(data->philos[i].pid, SIGTERM);
}

static int	ft_check(t_data *data, int *finished)
{
	int		stat;
	pid_t	pid;

	pid = waitpid(-1, &stat, 0);
	if (pid <= 0)
		return (-1);
	if (WIFEXITED(stat))
	{
		if (WEXITSTATUS(stat) == 1)
			return (1);
		else if (WEXITSTATUS(stat) == 0)
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
	while (42)
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
	t_philo	tmp;

	local = (t_local *)arg;
	data = local->data;
	while (42)
	{
		usleep(500);
		sem_wait(local->lock);
		elapsed = ft_gettime() - local->last_eat;
		sem_post(local->lock);
		if (elapsed >= data->args.die)
		{
			tmp.id = local->id;
			tmp.data = data;
			ft_write(&tmp, MSG_DIED);
			free(data->philos);
			exit(1);
		}
	}
	return (NULL);
}
