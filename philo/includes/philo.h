/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:20:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/15 22:40:17 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_settings
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	char			max_set;
	unsigned int	max_num_of_meal;
	struct timeval	start;
	pthread_mutex_t	write_mutex;
}			t_settings;

typedef struct s_phylo
{
	unsigned char		index;
	pthread_t			thread;
	t_settings			*settings;
	unsigned long long	last_meal;
	unsigned int		number_of_meal;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;

}				t_philo;

int					ft_atoi(const char *str);
void				display_action(const t_philo *phylo, char *action);
unsigned long long	get_time_stamp(struct timeval	start);
void				*eat_and_sleep(void *arg);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_philo				*parsing(int argc, char**argv, t_settings *settings);

#endif