/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/19 04:48:58 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_post(t_info *info)
{
	sem_post(info->forks);
	sem_post(info->forks);
}

void	start_philo(t_philo *philo)
{
	philo->eat_count = 0;
	philo->last_eat = time_in_ms(philo->info);
	if (philo->num % 2 == 0)
		usleep(10);
	while (philo->info->total != philo->info->num_philo && \
			!philo->info->dead)
	{
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork.");
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork.");
		print(philo, "is eating.");
		philo->eat_count++;
		if (philo->eat_count == philo->info->num_eat)
			philo->info->total++;
		ft_usleep(current_time() + philo->info->time_eat);
		philo->last_eat = time_in_ms(philo->info);
		ft_sem_post(philo->info);
		print(philo, "is sleeping.");
		ft_usleep(current_time() + philo->info->time_sleep);
		print(philo, "is thinking.");
	}
}
