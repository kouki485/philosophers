/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:41 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:33:42 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat(t_philo *philo)
{
	if (philo->has_fork_right == true && philo->has_fork_left == true)
	{
		pthread_mutex_lock(&philo->data->shared_mutex);
		philo->last_eat_time = get_time_zero_start(philo);
		pthread_mutex_unlock(&philo->data->shared_mutex);
		if (print_action(philo, "is eating") == 1 \
			|| time_keeper(philo, philo->data->time_to_eat) == 1)
			return (1);
		put_down_fork(philo);
		pthread_mutex_lock(&philo->data->shared_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->shared_mutex);
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_action(philo, "is sleeping") == 1 \
		|| time_keeper(philo, philo->data->time_to_sleep) == 1)
		return (1);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_action(philo, "is thinking") == 1)
		return (1);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->data->shared_mutex);
	philo->start_time = get_time_zero_start(philo);
	pthread_mutex_unlock(&philo->data->shared_mutex);
	if ((philo->philo_number % 2) == 0)
		usleep(200);
	while (1)
	{
		if (pickup_fork(philo) == 1 || philo_eat(philo) == 1 \
			|| philo_sleep(philo) == 1 || philo_think(philo))
			break ;
	}
	put_down_fork(philo);
	return (NULL);
}
