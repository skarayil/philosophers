/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 09:50:26 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

void	ft_parser(t_data *data, char *av[])
{
	data->args.philos = ft_atoi(av[1]);
	data->args.die = ft_atoi(av[2]);
	data->args.eat = ft_atoi(av[3]);
	data->args.sleep = ft_atoi(av[4]);
	if (av[5])
		data->args.limit = ft_atoi(av[5]);
	else
		data->args.limit = -1;
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		ft_error("Usage: ./philo_bonus number die eat sleep limit");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_init(&data, av))
		return (1);
	ft_parent(&data);
	ft_cleanup(&data);
	return (0);
}
