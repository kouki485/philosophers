/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:33:53 by kkohki            #+#    #+#             */
/*   Updated: 2022/05/25 22:37:30 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

long long	ft_atoll(const char *str)
{
	int			neg;
	size_t		i;
	long long	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg *= -1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * neg);
}

bool	digit_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if ((ft_strlen(argv[i]) > 1 && argv[i][0] == '0') || argv[i][0] == '0')
			return (false);
		if (ft_atoll(argv[i]) < 0 || INT_MAX < ft_atoll(argv[i]) \
			|| INT_MAX_RANGE < ft_strlen(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_isnum(int size, char **s)
{
	int	i;

	while (size > 0)
	{
		i = 0;
		while (s[size][i] >= '0' && s[size][i] <= '9')
			i++;
		if (s[size][i] != '\0')
			return (false);
		size--;
	}
	return (true);
}
