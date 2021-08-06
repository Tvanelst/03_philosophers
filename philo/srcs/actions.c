/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:40:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 19:06:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_phylo *phylo)
{
	//pthread_mutex_lock(fork);
	display_action(phylo, FORK);
}

void	eat_and_sleep(t_phylo *phylo)
{
	const t_settings			*settings = phylo->settings;
	const unsigned long long	start = get_time_stamp(settings->start);

	phylo->last_meal = start;
	display_action(phylo, EAT);
	while (get_time_stamp(settings->start) - start < settings->time_to_eat)
		usleep(1000);
	//pthread_mutex_unlock(first_fork)
	//pthread_mutex_unlock(second_fork)
	display_action(phylo, SLEEP);
	while (get_time_stamp(settings->start) - start
		< settings->time_to_sleep + settings->time_to_eat)
		usleep(1000);
	display_action(phylo, THINK);
}

void	die(t_phylo *phylo)
{
	display_action(phylo, DIED);
	//lock write access
	//end simulation
}