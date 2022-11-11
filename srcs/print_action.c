/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:44 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:35:29 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_help(void)
{
	printf(BLUE"Usage: [number of philosophers]");
	printf(BLUE"[time to die] [time to eat] [time to sleep]");
	printf(BLUE" [number of meals a philosopher has to eat]\n");
	printf(RESET"");
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1) && (*s2) && (n > 0))
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	print_action_color(t_philo *philo, char *message)
{
	if (ft_strncmp(philo->s[0], message, 17) == 0)
		printf("\x1b[31m%4zu \x1b[37m%d \x1b[36m%s\n", \
			get_time_zero_start(philo), philo->philo_number, message);
	if (ft_strncmp(philo->s[1], message, 12) == 0)
		printf("\x1b[31m%4zu \x1b[37m%d \x1b[35m%s\n", \
			get_time_zero_start(philo), philo->philo_number, message);
	if (ft_strncmp(philo->s[2], message, 12) == 0)
		printf("\x1b[31m%4zu \x1b[37m%d \x1b[32m%s\n", \
			get_time_zero_start(philo), philo->philo_number, message);
	if (ft_strncmp(philo->s[3], message, 4) == 0)
		printf("\x1b[31m%4zu \x1b[37m%d \x1b[31m%s\n", \
			get_time_zero_start(philo), philo->philo_number, message);
	if (ft_strncmp(philo->s[4], message, 10) == 0)
		printf("\x1b[31m%4zu \x1b[37m%d \x1b[34m%s\n", \
			get_time_zero_start(philo), philo->philo_number, message);
}

int	print_action(t_philo *philo, char *message)
{
	int	is_finished;

	philo->s[0] = "has taken a fork";
	philo->s[1] = "is sleeping";
	philo->s[2] = "is thinking";
	philo->s[3] = "died";
	philo->s[4] = "is eating";
	pthread_mutex_lock(&(philo->data->shared_mutex));
	is_finished = philo->data->is_finished;
	pthread_mutex_unlock(&(philo->data->shared_mutex));
	if (is_finished == 1)
	{
		printf(RESET"");
		return (1);
	}
	pthread_mutex_lock(&(philo->data->shared_mutex));
	print_action_color(philo, message);
	pthread_mutex_unlock(&(philo->data->shared_mutex));
	return (0);
}
