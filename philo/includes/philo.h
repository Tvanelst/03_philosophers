/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:20:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 18:50:31 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistdio.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_settings
{
	unsigned char	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	max_num_of_meal;
	struct timeval	start;
}			t_settings;

typedef struct s_phylo
{
	unsigned char		index;
	pthread_t			thread;
	t_settings			*settings;
	unsigned long long	last_meal;
}				t_phylo;

void	ft_putstr(char *str);
int		ft_atoi(const char *str);
void	display_action(const t_phylo *phylo, char *action);
unsigned long long	get_time_stamp(struct timeval	start);

#endif