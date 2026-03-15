/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:38 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 09:00:54 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static char	*ft_get_txt(t_msg msg)
{
	if (msg == MSG_TAKE_FORK)
		return ("has taken a fork");
	else if (msg == MSG_EATING)
		return ("is eating");
	else if (msg == MSG_SLEEPING)
		return ("is sleeping");
	else if (msg == MSG_THINKING)
		return ("is thinking");
	else if (msg == MSG_DIED)
		return ("died");
	else
		return ("All philosophers have eaten enough");
}

static char	*ft_get_clr(t_msg msg)
{
	if (msg == MSG_TAKE_FORK)
		return (GREEN);
	else if (msg == MSG_EATING)
		return (BLUE);
	else if (msg == MSG_SLEEPING)
		return (PURPLE);
	else if (msg == MSG_THINKING)
		return (GREY);
	else if (msg == MSG_DIED)
		return (RED);
	else
		return (WHITE);
}

static int	ft_buf(char *buf, char *src, long n, int i)
{
	int		len;
	long	tmp;

	if (n != -1)
	{
		len = 0;
		tmp = n;
		if (tmp == 0)
			len = 1;
		while (tmp > 0 && ++len)
			tmp /= 10;
		tmp = i + len;
		while (len--)
		{
			buf[i + len] = (n % 10) + '0';
			n /= 10;
		}
		i = tmp;
	}
	while (src && *src)
		buf[i++] = *src++;
	return (i);
}

static int	ft_build(t_philo *philo, t_msg msg, char *buf)
{
	int		i;
	long	time;

	i = 0;
	time = ft_gettime() - philo->data->start;
	i = ft_buf(buf, ft_get_clr(msg), -1, i);
	buf[i++] = '[';
	i = ft_buf(buf, "] ", time, i);
	if (msg != MSG_FINISHED)
	{
		i = ft_buf(buf, "", philo->id, i);
		buf[i++] = ' ';
	}
	i = ft_buf(buf, ft_get_txt(msg), -1, i);
	i = ft_buf(buf, "\033[0m\n", -1, i);
	return (i);
}

void	ft_write(t_philo *philo, t_msg msg)
{
	char	buf[256];
	int		len;

	pthread_mutex_lock(&philo->data->mtx.write);
	pthread_mutex_lock(&philo->data->mtx.dead);
	if (philo->data->alive == false && msg != MSG_DIED)
	{
		pthread_mutex_unlock(&philo->data->mtx.dead);
		pthread_mutex_unlock(&philo->data->mtx.write);
		return ;
	}
	len = ft_build(philo, msg, buf);
	write(1, buf, len);
	if (msg == MSG_DIED)
		philo->data->alive = false;
	pthread_mutex_unlock(&philo->data->mtx.dead);
	pthread_mutex_unlock(&philo->data->mtx.write);
}
