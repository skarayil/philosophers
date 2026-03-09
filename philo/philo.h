/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:53:57 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/27 16:30:16 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_data	t_data;

typedef enum e_msg
{
	MSG_TAKE_FORK,
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DIED,
	MSG_FINISHED
}						t_msg;

typedef struct s_args
{
	int					philos;
	int					die;
	int					eat;
	int					sleep;
	int					limit;
}						t_args;

typedef struct s_mtx
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		dead;
	pthread_mutex_t		meal;
}						t_mtx;

typedef struct s_philo
{
	int					id;
	int					time_eat;
	long				last_eat;
	pthread_t			thread;
	pthread_mutex_t		*port;
	pthread_mutex_t		*star;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	bool				alive;
	long				start;
	t_args				args;
	t_mtx				mtx;
	t_philo				*philos;
}						t_data;

int						ft_atoi(const char *str);
void					ft_putstr_fd(char *str, int fd);
void					*ft_memset(void *str, int c, size_t n);
void					*ft_monitor(void *arg);
void					ft_putnbr_fd(long n, int fd);
void					*ft_routine(void *arg);
void					ft_write(t_philo *philo, t_msg msg);
bool					ft_init(t_data *data, char *av[]);
bool					ft_usleep(long ms, t_data *data);
bool					ft_error(char *str);
long					ft_gettime(void);

#endif