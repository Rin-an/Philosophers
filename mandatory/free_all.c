/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:15:27 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/20 15:26:30 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		pthread_mutex_destroy(info->philo[i].lfork);
		pthread_mutex_destroy(info->philo[i].rfork);
		pthread_mutex_destroy(&(info->fork[i]));
	}
	pthread_mutex_destroy(&(info->lock));
	pthread_mutex_destroy(info->fork);
	free(info->philo);
	free(info);
}
