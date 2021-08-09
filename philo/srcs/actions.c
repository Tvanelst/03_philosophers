/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:40:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/09 12:23:27 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	const char	offset = philo->index % philo->settings->number_of_philos;

	pthread_mutex_lock(philo->fork_l + offset % 2);
	display_action(philo, FORK);
	if (philo->index % 2)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	display_action(philo, FORK);
	philo->last_meal = get_time_stamp(philo->settings->start);
	display_action(philo, EAT);
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
		take_forks(philo);
		while (get_time_stamp(settings->start) - philo->last_meal
			< settings->time_to_eat)
			usleep(900);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		philo->number_of_meal++;
		display_action(philo, SLEEP);
		while (get_time_stamp(settings->start) - philo->last_meal
			< settings->time_to_sleep + settings->time_to_eat)
			usleep(900);
		display_action(philo, THINK);
	}
	return (NULL);
}
