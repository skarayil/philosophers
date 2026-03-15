/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/15 10:05:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
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
	else
		return ("died");
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
	else
		return (RED);
}

static int	ft_buf(char *buf, char *src, long n, int i)
{
	int		len;
	long	tmp;

	if (n != -1)
	{
		tmp = n;
		if (tmp == 0)
			len = 1;
		else
			len = 0;
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
	i = ft_buf(buf, NULL, time, i);
	i = ft_buf(buf, "] ", -1, i);
	i = ft_buf(buf, NULL, philo->id, i);
	buf[i++] = ' ';
	i = ft_buf(buf, ft_get_txt(msg), -1, i);
	i = ft_buf(buf, RESET, -1, i);
	buf[i++] = '\n';
	return (i);
}

void	ft_write(t_philo *philo, t_msg msg)
{
	char	buf[256];
	int		len;

	sem_wait(philo->data->sem.write);
	len = ft_build(philo, msg, buf);
	write(1, buf, len);
	if (msg != MSG_DIED)
		sem_post(philo->data->sem.write);
}
