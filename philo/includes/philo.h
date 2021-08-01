/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:20:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/01 19:22:45 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistdio.h>
# include <unistd.h>

typedef struct s_settings
{
	unsigned char	number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_num_of_meal;
}			t_settings;

typedef struct s_phylo
{
	unsigned char	index;
	pthread_t		thread;
	t_settings		*settings;
}				t_phylo;

void	ft_putstr(char *str);
int		ft_atoi(const char *str);

#endif