/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/20 04:50:41 by ssadiki          ###   ########.fr       */
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
	philo->last_eat = time_in_ms(philo->info);
	while (!philo->dead && philo->eat_count != philo->info->num_eat)
	{
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork.");
		sem_wait(philo->info->forks);
		print(philo, "has taken a fork.");
		print(philo, "is eating.");
		philo->eat_count++;
		ft_usleep(current_time() + philo->info->time_eat);
		philo->last_eat = time_in_ms(philo->info);
		ft_sem_post(philo->info);
		print(philo, "is sleeping.");
		ft_usleep(current_time() + philo->info->time_sleep);
		print(philo, "is thinking.");
	}
	printf("Philo %i got out\n",philo->num);
}
