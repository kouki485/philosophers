/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:50 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:33:51 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_time_zero_start(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->start_time);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	time_keeper(t_philo *philo, size_t time)
{
	size_t	start_time;
	size_t	passed_time;
	bool	is_finished;

	pthread_mutex_lock(&philo->data->shared_mutex);
	start_time = get_time_zero_start(philo);
	pthread_mutex_unlock(&philo->data->shared_mutex);
	while (1)
	{
		passed_time = get_time_zero_start(philo);
		if (passed_time - start_time >= time)
			return (0);
		pthread_mutex_lock(&philo->data->shared_mutex);
		is_finished = philo->data->is_finished;
		pthread_mutex_unlock(&philo->data->shared_mutex);
		if (is_finished == true)
			return (1);
		usleep(100);
	}
}
