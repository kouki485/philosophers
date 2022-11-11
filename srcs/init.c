/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:31 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:33:32 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i].has_fork_right = false;
		data->philos[i].has_fork_left = false;
		data->philos[i].is_reached_min_eat = false;
		data->philos[i].eat_count = 0;
		data->philos[i].philo_number = i + 1;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

static bool	init_monitors(t_data *data)
{
	data->monitor.data = data;
	return (true);
}

static bool	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&(data->forks_mutex[i]), NULL);
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	if (ft_atoll(argv[1]) > 200)
	{
		printf(RED"Too many philosophers \n");
		return (false);
	}
	data->number_of_philo = (int)ft_atoll(argv[1]);
	data->time_to_die = (int)ft_atoll(argv[2]);
	data->time_to_eat = (int)ft_atoll(argv[3]);
	data->time_to_sleep = (int)ft_atoll(argv[4]);
	data->argc = argc;
	data->is_finished = 0;
	if (argc == 6)
		data->number_of_min_eat = (int)ft_atoll(argv[5]);
	else
		data->number_of_min_eat = 0;
	pthread_mutex_init(&(data->shared_mutex), NULL);
	init_philos(data);
	init_forks(data);
	init_monitors(data);
	return (true);
}
