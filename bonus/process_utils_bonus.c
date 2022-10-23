/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:59:05 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/23 16:38:19 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		kill(info->pid[i], SIGINT);
}

void	create_process(t_info **info)
{
	int	i;

	i = -1;
	while (++i < (*info)->num_philo)
	{
		(*info)->pid[i] = fork();
		if (!(*info)->pid[i])
		{
			(*info)->philo[i].last_eat = time_in_ms(*info);
			if (pthread_create(&(*info)->philo[i].id, NULL, &monitor,
					&(*info)->philo[i]))
				return ;
			start_philo(&(*info)->philo[i]);
			if (!pthread_detach((*info)->philo[i].id))
				return ;
		}
	}
}
