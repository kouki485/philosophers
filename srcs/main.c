/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:34 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:33:35 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->shared_mutex);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if ((argc != 5 && argc != 6) || \
		ft_isnum(argc - 1, argv) == false || digit_check(argc, argv) == false)
	{
		printf(RED"Invalid input!\n");
		print_help();
		return (0);
	}
	if (init_data(&data, argc, argv) == false)
		return (0);
	create_thread(&data);
	join_thread(&data);
	destroy_mutex(&data);
	return (0);
}
