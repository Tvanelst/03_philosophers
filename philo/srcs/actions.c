/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:40:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/10 09:56:58 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_and_eat(t_philo *philo)
{
	const t_settings	*settings = philo->settings;
	const char			offset = philo->index % settings->number_of_philos % 2;

	pthread_mutex_lock(philo->fork_l + offset);
	display_action(philo, FORK);
	pthread_mutex_lock(philo->fork_r - offset);
	display_action(philo, FORK);
	philo->last_meal = get_time_stamp(settings->start);
	display_action(philo, EAT);
	philo->number_of_meal++;
	usleep(settings->time_to_eat * 800);
	while (get_time_stamp(settings->start) - philo->last_meal
		< settings->time_to_eat)
		usleep(50);
}

void	*eat_and_sleep(void *arg)
{
	const t_settings	*settings = ((t_philo *)arg)->settings;
	t_philo				*philo;

	philo = (t_philo *)arg;
	if (!(philo->index % 2))
		usleep(settings->time_to_eat * 500);
	while (!settings->max_set || (settings->max_num_of_meal
			&& philo->number_of_meal < settings->max_num_of_meal))
	{
		take_forks_and_eat(philo);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		display_action(philo, SLEEP);
		usleep(philo->settings->time_to_sleep * 800);
		while (get_time_stamp(settings->start) - philo->last_meal
			< settings->time_to_sleep + settings->time_to_eat)
			usleep(50);
		if (!settings->max_set
			|| philo->number_of_meal < settings->max_num_of_meal)
			display_action(philo, THINK);
		usleep(500);
	}
	return (NULL);
}
