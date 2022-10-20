/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:03:11 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/20 04:50:39 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_process(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		waitpid(info->pid[i], NULL, 0);
}
void	process_start(t_info **info, int i)
{
//	int	i;

//	i = -1;
//	while (++i < (*info)->num_philo)
//	{
		(*info)->philo[i].num = i + 1;
		(*info)->philo[i].info = *info;
		(*info)->philo[i].dead = 0;
		(*info)->philo[i].eat_count = 0;
	//	(*info)->pid[i] = fork();
	//	if ((*info)->pid[i] == 0)
	//	{
		pthread_create(&((*info)->philo[i].id), NULL, &monitor, \
				&((*info)->philo[i]));
		start_philo(&(*info)->philo[i]);
		pthread_detach((*info)->philo[i].id);
		//}
//	}
}

void	init_process(t_info **info)
{
	int	i;

	i = -1;
	while (++i < (*info)->num_philo)
	{
		(*info)->pid[i] = fork();
		if ((*info)->pid[i] == 0)
			process_start(info, i);
	}
}

void	kill_process(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		kill(info->pid[i], SIGINT);
}

