/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:15:27 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/19 04:00:23 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_all(t_info *info)
{
	int	i;

	i = -1;
	sem_close(info->forks);
	sem_close(info->lock);
	sem_unlink("forks");
	sem_unlink("lock");
	while (++i < info->num_philo)
		kill(info->philo[i].pid, SIGINT);
	free(info->philo);
	free(info);
}
