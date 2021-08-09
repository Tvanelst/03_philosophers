/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:41:53 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/09 15:42:52 by tvanelst         ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;
	unsigned long	limit;

	result = 0;
	limit = __LONG_MAX__ / 10;
	sign = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while ('0' <= *str && *str <= '9')
	{
		if ((result == limit && (*str - '0') > 6 - sign) || result > limit)
			return (-sign - 1);
		result = result * 10 + *str++ - '0';
	}
	if (sign)
		return (result * sign);
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
		if (*s1++ != *s2++)
			return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
	return (0);
}

void	display_action(const t_philo *phylo, char *action)
{
	unsigned long long	time_stamp;

	pthread_mutex_lock(&phylo->settings->write_mutex);
	time_stamp = get_time_stamp(phylo->settings->start);
	printf("%llu %d %s\n", time_stamp, phylo->index, action);
	if (ft_strncmp(action, DIED, 5))
		pthread_mutex_unlock(&phylo->settings->write_mutex);
	else
		usleep(200000);
}
