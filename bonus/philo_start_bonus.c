/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/23 16:30:36 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put_forks(t_philo *philo)
{
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
}

void	start_philo(t_philo *philo)
{
	if (philo->num % 2 == 0)
		usleep(10);
	while (1)
	{
		sem_wait(philo->info->fork);
		print(philo, "has taken a fork.");
		sem_wait(philo->info->fork);
		print(philo, "has taken a fork.");
		print(philo, "is eating.");
		philo->eat_count++;
		ft_usleep(current_time() + philo->info->time_eat);
		philo->last_eat = time_in_ms(philo->info);
		put_forks(philo);
		print(philo, "is sleeping.");
		ft_usleep(current_time() + philo->info->time_sleep);
		print(philo, "is thinking.");
	}
	return ;
}
