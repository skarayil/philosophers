/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 02:29:43 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <limits.h>

static bool	ft_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	ft_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

int	ft_atoi(const char *str)
{
	long	sign;
	long	sum;
	long	tmp;

	sign = 1;
	sum = 0;
	while (ft_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_digit(*str))
	{
		tmp = sum * 10 + (*str - '0');
		if (sign == 1 && tmp > INT_MAX)
			return (-1);
		if (sign == -1 && - tmp < INT_MIN)
			return (-1);
		sum = tmp;
		str++;
	}
	return ((int)(sum * sign));
}
