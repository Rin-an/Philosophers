/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:57:52 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/16 15:19:35 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_info *info)
{
	int	i;
	int	count;

	count = 0;
	while (1)
	{
		pthread_mutex_lock(&info->lock);
		i = -1;
		while (++i < info->num_philo)
		{
			if ((current_time() - info->init) - info->philo[i].last_eat >= info->time_die)
			{
				info->dead = 1;
				printf("%li ms %i died.\n", current_time() - \
						info->init, i + 1);
				usleep(100);
				pthread_mutex_unlock(&info->lock);
				return ;
			}
		}
		pthread_mutex_unlock(&info->lock);
		usleep(100);
	}
}
