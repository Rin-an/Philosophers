/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:59:05 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/22 10:09:59 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_info *info)
{
	int	i;
	
	i = -1;
	while (++i < info->num_philo)
	{
		printf("i = %i\n",i);
		kill(info->pid[i], SIGINT);
	}
	return ;
}

void	create_process(t_info **info)
{
	int	i;

	i = -1;
	while (++i < (*info)->num_philo)
	{
		printf("how about here then\n");
		(*info)->pid[i] = fork();
		if (!(*info)->pid[i])
		{
			(*info)->philo[i].last_eat = time_in_ms(*info);
			if (pthread_create(&(*info)->philo[i].id, NULL, &monitor, 
				&(*info)->philo[i]))
				return ;
			start_philo(&(*info)->philo[i]);
		//	pthread_detach(info->philo[i].id);
		}
	}
}

void	wait_process(t_info *info)
{
	(void)info;
	/*int	i;

	i = -1;
	while (++i < info->num_philo)
		waitpid(info->pid[i], 0, 0);*/
	while (!waitpid(0, 0 ,0))
	{
		printf("Allo\n");
	}
}
