/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 20:56:46 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/15 22:41:43 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	is_int(const char *str)
{
	if (*str == '-')
	{
		str++;
		if (!ft_isdigit(*str))
			return (0);
	}
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	max_int_value(const char *str)
{
	long	n;
	char	sign;

	n = 0;
	sign = (*str == '-');
	if (sign)
		str++;
	while (*str)
	{
		n *= 10;
		n += *str++ - '0';
		if (n > (long)INT32_MAX + sign)
			return (0);
	}
	return (1);
}

int	get_value(const char *str, unsigned int *var)
{
	if (!is_int(str) || !max_int_value(str))
		return (0);
	*var = ft_atoi(str);
	return (1);
}

t_philo	*parsing(int argc, char**argv, t_settings *settings)
{
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (NULL);
	}
	if (!get_value(argv[1], &settings->number_of_philos)
		|| !get_value(argv[2], &settings->time_to_die)
		|| !get_value(argv[3], &settings->time_to_eat)
		|| !get_value(argv[4], &settings->time_to_sleep))
		return (0);
	settings->max_set = 0;
	if (gettimeofday(&settings->start, 0))
	{
		printf("gettimeofday fail\n");
		return (NULL);
	}
	if (argc == 6 && ++settings->max_set)
		get_value(argv[5], &settings->max_num_of_meal);
	philos = malloc((sizeof(*philos) + sizeof(pthread_mutex_t))
			* settings->number_of_philos);
	if (!philos)
		printf("malloc fail\n");
	return (philos);
}
