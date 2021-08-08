/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:18:30 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/08 17:22:24 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time_stamp(struct timeval	start)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	return ((now.tv_sec - start.tv_sec) * 1000
		+ (now.tv_usec - start.tv_usec) / 1000);
}

void	display_action(const t_philo *phylo, char *action)
{
	const unsigned long long time_stamp = get_time_stamp(phylo->settings->start);

	pthread_mutex_lock(&phylo->settings->write_mutex);
	printf("%llu %d %s\n", time_stamp, phylo->index, action);
	if (ft_strncmp(action, DIED, 5))
		pthread_mutex_unlock(&phylo->settings->write_mutex);
	else
	{
		pthread_mutex_destroy(&phylo->settings->write_mutex);
		usleep(200000);
	}
}

void	*routine(void *arg)
{
	t_philo	*phylo;

	phylo = (t_philo *)arg;
	while (1)
		if (!eat_and_sleep(phylo))
			break;
	return (NULL);
}

static t_philo	*parsing(int argc, char**argv, t_settings *settings)
{
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		ft_putstr("usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (NULL);
	}
	settings->number_of_philos = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	settings->max_num_of_meal = -1;
	if (gettimeofday(&settings->start, 0))
	{
		ft_putstr("gettimeofday fail");
		return (NULL);
	}
	if (argc == 6)
		settings->max_num_of_meal = ft_atoi(argv[5]);
	philos = malloc((sizeof(*philos) + sizeof(pthread_mutex_t))
		* settings->number_of_philos);
	if (!philos)
		ft_putstr("malloc fail");
	return (philos);
}

int	init_forks(pthread_mutex_t *forks, unsigned char index)
{
	while (index--)
		if (pthread_mutex_init(forks + index, 0))
			return (0);
	return (1);
}

int	destroy_forks(pthread_mutex_t *forks, unsigned char index)
{
	while (index--)
		if (pthread_mutex_destroy(forks + index))
			return (0);
	return (1);
}

char	check_for_death(t_philo *philo, t_settings *settings)
{
	const unsigned long long now = get_time_stamp(philo->settings->start);
	unsigned char	i;

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
	return(0);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_settings		settings;
	unsigned char	index;

	philos = parsing(argc, argv, &settings);
	if (!philos)
		return (1);
	forks = (pthread_mutex_t *)(philos + settings.number_of_philos);
	if (!init_forks(forks, settings.number_of_philos))
		return (2);
	pthread_mutex_init(&settings.write_mutex, 0);
	index = 0;
	while (index < settings.number_of_philos)
	{
		philos->settings = &settings;
		philos->fork_l = forks + index++;
		philos->fork_r = forks + (index % settings.number_of_philos);
		philos->last_meal = get_time_stamp(settings.start);
		philos->index = index;
		if (pthread_create(&philos->thread, NULL, routine, philos))
			break ;//error creating threads + free(philo)
		philos++;
	}
	while (!check_for_death(philos - index, &settings))
		usleep(1000);
	destroy_forks(forks, settings.number_of_philos);
	free(philos - index);
	return (0);
}
