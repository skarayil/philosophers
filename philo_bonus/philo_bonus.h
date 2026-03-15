/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 09:58:28 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/15 09:58:28 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdbool.h>

# define PURPLE "\033[95m"
# define GREEN "\033[1;32m"
# define GREY "\033[1;30m"
# define BLUE "\033[94m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_data	t_data;

typedef enum e_msg
{
	MSG_TAKE_FORK,
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DIED
}						t_msg;

typedef struct s_args
{
	int					philos;
	int					die;
	int					eat;
	int					sleep;
	int					limit;
}						t_args;

typedef struct s_sem
{
	sem_t				*forks;
	sem_t				*turn;
	sem_t				*write;
}						t_sem;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	t_args				args;
	t_sem				sem;
	t_philo				*philos;
	long				start;
}						t_data;

typedef struct s_local
{
	int					id;
	long				last_eat;
	int					time_eat;
	sem_t				*lock;
	t_data				*data;
}						t_local;

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	*ft_memset(void *str, int c, size_t n);
long	ft_gettime(void);
bool	ft_error(char *str);
bool	ft_usleep(long ms);
bool	ft_init(t_data *data, char *av[]);
void	ft_cleanup(t_data *data);
void	ft_child(t_philo *philo);
void	ft_parent(t_data *data);
void	ft_write(t_philo *philo, t_msg msg);
void	ft_parser(t_data *data, char *av[]);
void	ft_itoa(int n, char *buf);
void	ft_strcat(char *dest, const char *src);
void	ft_eat(t_local *philo, t_data *data);
void	ft_sleep_think(t_local *philo, t_data *data);
void	ft_meal(t_local *local, char *name,	t_data *data);
void	*ft_monitor(void *arg);

#endif
