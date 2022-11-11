/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:37:56 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:42:38 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define INT_MAX_RANGE 11

typedef struct s_data	t_data;

typedef struct s_philo
{
	bool		has_fork_right;
	bool		has_fork_left;
	bool		is_reached_min_eat;
	int			philo_number;
	size_t		eat_count;
	size_t		last_eat_time;
	size_t		start_time;
	pthread_t	thread_philo;
	t_data		*data;
	char		*s[5];
}	t_philo;

typedef struct s_monitor
{
	pthread_t	thread_monitor;
	t_data		*data;
}	t_monitor;

typedef struct s_data
{
	int				number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_min_eat;
	bool			is_finished;

	t_philo			philos[256];
	t_monitor		monitor;
	pthread_mutex_t	shared_mutex;
	pthread_mutex_t	forks_mutex[256];
	int				argc;
}	t_data;

//init.c
bool		init_data(t_data *data, int argc, char **argv);

//thread.c
void		create_thread(t_data *data);
void		join_thread(t_data *data);

//fork.c
int			pickup_fork(t_philo *philo);
void		put_down_fork(t_philo *philo);

//philo_action.c
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
void		*philo_routine(void *ptr);

//eat.c
int			philo_eat(t_philo *philo);

//time.c
int			time_keeper(t_philo *philo, size_t time);
size_t		get_time(void);

//monitor.c
void		*monitor_routine(void *ptr);

//print_action.c
void		print_help(void);
size_t		get_time_zero_start(t_philo *philo);
int			print_action(t_philo *philo, char *message);

//utils.c
long long	ft_atoll(const char *str);
bool		digit_check(int argc, char **argv);
bool		ft_isnum(int size, char **s);
#endif