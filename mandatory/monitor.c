/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:57:52 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/17 18:10:50 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_info *info)
{
	int	i;

	while (1)
	{
		if (info->total == info->num_philo)
			return ;
		i = -1;
		while (++i < info->num_philo)
		{
			if (time_in_ms(info) - info->philo[i].last_eat > info->time_die)
			{
				pthread_mutex_lock(&info->lock);
				printf("%li ms %i died.\n", current_time() - info->init, i + 1);
				return ;
			}
		}
		usleep(50);
	}
}
