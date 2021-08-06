/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:18:30 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 17:25:17 by tvanelst         ###   ########.fr       */
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

void	display_action(const t_phylo *phylo, char *action)
{
	const unsigned long long time_stamp = get_time_stamp(phylo->settings->start);

	printf("%llu %d %s\n", time_stamp, phylo->index, action);
}

void	*routine(void *arg)
{
	const	t_phylo *phylo = (t_phylo *)arg;

	printf("phylo index = %d is created at %llu\n", phylo->index, get_time_stamp(phylo->settings->start));
	display_action(phylo, FORK);
	return (NULL);
}

static t_phylo	*parsing(int argc, char**argv, t_settings *settings)
{
	t_phylo	*philos;

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
	philos = malloc(sizeof(*philos) * settings->number_of_philos);
	if (!philos)
		ft_putstr("malloc fail");
	return (philos);
}

int	main(int argc, char **argv)
{
	t_phylo			*philos;
	t_settings		settings;
	unsigned char	index;
	//pthread_mutex_t	mutex;

	philos = parsing(argc, argv, &settings);
	if (!philos)
		return (1);
	index = 0;
	while (index < settings.number_of_philos)
	{
		philos->settings = &settings;
		philos->index = index++;
		if (pthread_create(&philos->thread, NULL, routine, philos))
			break ;//error creating threads + free(philo)
		//pthread_join();
		philos++;
		usleep(50000);
	}
	//pthread_mutex_init():
	free(philos - index);
	return (0);
}
