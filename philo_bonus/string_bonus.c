/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 02:44:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_itoa_buf(int n, char *buf)
{
	long	num;
	int		i;
	int		len;

	num = n;
	if (num == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return ;
	}
	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	buf[len] = '\0';
	num = n;
	i = len;
	while (i-- > 0)
	{
		buf[i] = (num % 10) + '0';
		num /= 10;
	}
}

void	ft_strcat_buf(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}
