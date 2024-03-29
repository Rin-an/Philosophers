/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/17 15:49:06 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	*start_philo(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *) vargp;
	philo->eat_count = 0;
	philo->last_eat = time_in_ms(philo->info);
	if (philo->num % 2 == 0)
		usleep(10);
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		print(philo, "has taken a fork.");
		pthread_mutex_lock(philo->rfork);
		print(philo, "has taken a fork.");
		print(philo, "is eating.");
		philo->eat_count++;
		if (philo->eat_count == philo->info->num_eat)
			philo->info->total++;
		ft_usleep(current_time() + philo->info->time_eat);
		philo->last_eat = time_in_ms(philo->info);
		put_forks(philo);
		print(philo, "is sleeping.");
		ft_usleep(current_time() + philo->info->time_sleep);
		print(philo, "is thinking.");
	}
	return (NULL);
}
