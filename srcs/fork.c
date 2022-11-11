/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:28 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:40:44 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_down_fork(t_philo *philo)
{
	if (philo->has_fork_left == true)
	{
		if (philo->philo_number == philo->data->number_of_philo)
			pthread_mutex_unlock(&philo->data->forks_mutex[0]);
		else
			pthread_mutex_unlock \
			(&philo->data->forks_mutex[philo->philo_number]);
		philo->has_fork_left = false;
	}
	if (philo->has_fork_right == true)
	{
		pthread_mutex_unlock \
		(&philo->data->forks_mutex[philo->philo_number - 1]);
		philo->has_fork_right = false;
	}
}

static int	pickup_left(t_philo *philo)
{
	if (philo->has_fork_left == false)
	{
		if (philo->philo_number != philo->data->number_of_philo)
		{
			pthread_mutex_lock \
			(&(philo->data->forks_mutex[philo->philo_number]));
			philo->has_fork_left = true;
			if (print_action(philo, "has taken a fork") == 1)
				return (1);
		}
		else if (philo->data->number_of_philo != 1)
		{
			pthread_mutex_lock(&(philo->data->forks_mutex[0]));
			philo->has_fork_left = true;
			if (print_action(philo, "has taken a fork") == 1)
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

static int	pickup_right(t_philo *philo)
{
	if (philo->has_fork_right == false)
	{
		pthread_mutex_lock \
			(&(philo->data->forks_mutex[philo->philo_number - 1]));
		philo->has_fork_right = true;
		if (print_action(philo, "has taken a fork") == 1)
			return (1);
	}
	return (0);
}

int	pickup_fork(t_philo *philo)
{
	if (pickup_right(philo) == 1 || pickup_left(philo) == 1)
		return (1);
	return (0);
}
