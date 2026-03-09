/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:45:40 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/07 14:02:43 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>

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
