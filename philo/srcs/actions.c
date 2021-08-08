/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:40:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/08 17:32:45 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->index % 2)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	display_action(philo, FORK);
	if (philo->index % 2)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	display_action(philo, FORK);
}

char	eat_and_sleep(t_philo *philo)
{
	const t_settings	*settings = philo->settings;

	if (philo->index % 2 && philo->last_meal < 10)
		usleep(1000);
	take_forks(philo);
	philo->last_meal = get_time_stamp(settings->start);
	display_action(philo, EAT);
	while (get_time_stamp(settings->start) - philo->last_meal < settings->time_to_eat)
		usleep(1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	display_action(philo, SLEEP);
	while (get_time_stamp(settings->start) - philo->last_meal
		< settings->time_to_sleep + settings->time_to_eat)
		usleep(1000);
	display_action(philo, THINK);
	return (1);
}
