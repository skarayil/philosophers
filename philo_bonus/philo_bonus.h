/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/03/09 02:49:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>

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
	long				start_time;
}						t_data;

typedef struct s_local
{
	int					id;
	long				last_meal;
	int					eat_count;
	sem_t				*meal_lock;
	t_data				*data;
}						t_local;

int						ft_atoi(const char *str);
void					ft_putstr_fd(char *str, int fd);
void					*ft_memset(void *str, int c, size_t n);
long					ft_gettime(void);
bool					ft_error(char *str);
bool					ft_usleep(long ms);
bool					ft_init(t_data *data, char *av[]);
void					ft_cleanup(t_data *data);
void					ft_child_routine(t_philo *philo);
void					ft_parent_monitor(t_data *data);
void					ft_write(t_philo *philo, t_msg msg);
void					ft_parser(t_data *data, char *av[]);
void					ft_itoa_buf(int n, char *buf);
void					ft_strcat_buf(char *dest, const char *src);
void					ft_eat(t_local *philo, t_data *data);
void					ft_sleep_think(t_local *philo, t_data *data);
void					create_meal_semaphore(t_local *local, char *sem_name,
							t_data *data);
void					*monitor_thread(void *arg);

#endif