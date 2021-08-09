/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:18:30 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/09 15:36:09 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*parsing(int argc, char**argv, t_settings *settings)
{
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (NULL);
	}
	settings->number_of_philos = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	settings->max_set = 0;
	if (gettimeofday(&settings->start, 0))
	{
		printf("gettimeofday fail");
		return (NULL);
	}
	if (argc == 6)
	{
		settings->max_set = 1;
		settings->max_num_of_meal = ft_atoi(argv[5]);
	}
	philos = malloc((sizeof(*philos) + sizeof(pthread_mutex_t))
			* settings->number_of_philos);
	if (!philos)
		printf("malloc fail");
	return (philos);
}

static pthread_mutex_t	*init_philos_and_forks(t_philo *philos, t_settings *settings)
{
	pthread_mutex_t	*forks;
	unsigned char	index;

	forks = (pthread_mutex_t *)(philos + settings->number_of_philos);
	index = 0;
	while (index < settings->number_of_philos)
		if (pthread_mutex_init(forks + index++, 0))
			return (0);
	if (pthread_mutex_init(&settings->write_mutex, 0))
		return (0);
	index = 0;
	while (index < settings->number_of_philos)
	{
		philos->settings = settings;
		philos->number_of_meal = 0;
		philos->fork_l = forks + index++;
		philos->fork_r = forks + (index % settings->number_of_philos);
		philos->last_meal = get_time_stamp(settings->start);
		philos->index = index;
		if (pthread_create(&philos->thread, NULL, eat_and_sleep, philos))
			return (0);
		philos++;
	}
	return (forks);
}

static int	destroy_philos_and_forks(pthread_mutex_t *forks, unsigned char index)
{
	while (index--)
		if (pthread_mutex_destroy(forks + index))
			return (0);
	return (1);
}

static char	check_for_end(t_philo *philo, t_settings *settings)
{
	const unsigned long long	now = get_time_stamp(philo->settings->start);
	unsigned char				i;

	i = 0;
	while (settings->max_set && i < settings->number_of_philos
		&& (philo + i)->number_of_meal == settings->max_num_of_meal)
		if (++i == settings->number_of_philos)
			return (1);
	i = 0;
	while (i++ < settings->number_of_philos)
	{
		if (now - philo->last_meal > philo->settings->time_to_die)
		{
			display_action(philo, DIED);
			return (1);
		}
		philo++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_settings		settings;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = parsing(argc, argv, &settings);
	if (!philos)
		return (1);
	forks = init_philos_and_forks(philos, &settings);
	if (!forks)
		return (2);
	while (!check_for_end(philos, &settings))
		usleep(800);
	destroy_philos_and_forks(forks, settings.number_of_philos);
	free(philos);
	pthread_mutex_destroy(&settings.write_mutex);
	return (0);
}
