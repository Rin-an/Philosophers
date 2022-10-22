/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:15:27 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/22 04:02:03 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_all(t_info *info)
{
	int	i;

	i = -1;
	sem_unlink("forks");
	sem_unlink("lock");
	sem_close(info->lock);
	sem_close(info->fork);
	free(info->philo);
	free(info->pid);
	free(info);
	exit(0);
}
