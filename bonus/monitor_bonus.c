/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:57:52 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/19 04:48:59 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *vargp)
{
	t_info	*info;

	info = (t_info *) vargp;
	int	i;

	while (1)
	{
		if (info->total == info->num_philo)
			return (NULL);
		i = -1;
		while (++i < info->num_philo)
		{
			if (time_in_ms(info) - info->philo[i].last_eat > info->time_die)
			{
				info->dead = 1;
				sem_wait(info->lock);
				printf("%li ms %i died.\n", current_time() - info->init, i + 1);
			}
			break ;
		}
		usleep(50);
	}
	destroy_all(info);
	return (NULL);
}
