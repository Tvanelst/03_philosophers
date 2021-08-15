/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:18:30 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/16 00:45:25 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_philos_and_forks(t_philo *philos,
		t_settings *settings)
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
		philos->last_meal = 0;
		philos->index = index;
		if (pthread_create(&philos->thread, NULL, eat_and_sleep, philos))
			return (0);
		philos++;
	}
	return (forks);
}

static int	destroy_philos_and_forks(pthread_mutex_t *forks,
		unsigned char index)
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
	{
		if (++i == settings->number_of_philos)
		{
			pthread_mutex_lock(&settings->write_mutex);
			usleep(200000);
			return (1);
		}
	}
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
	if (settings.number_of_philos)
	{
		forks = init_philos_and_forks(philos, &settings);
		if (forks)
			while (!check_for_end(philos, &settings))
				usleep(800);
		destroy_philos_and_forks(forks, settings.number_of_philos);
		pthread_mutex_destroy(&settings.write_mutex);
	}
	free(philos);
	return (0);
}
