/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/16 12:28:09 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_number(t_philo *philo)
{
	if (pthread_mutex_lock(philo->rfork))
	{
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	if (!philosopher_dead(philo))
		print(philo, "has taken a fork.");
	return (0);
}

int	odd_number(t_philo *philo)
{
	if (pthread_mutex_lock(philo->lfork))
	{
		pthread_mutex_unlock(philo->rfork);
		return (1);
	}
	if (!philosopher_dead(philo))
		print(philo, "has taken a fork.");
	return (0);
}

void	take_forks(t_philo *philo)
{
	if (philo->num % 2 != 0)
		pthread_mutex_lock(philo->lfork);
	else
		pthread_mutex_lock(philo->rfork);
	if (!philosopher_dead(philo))
		print(philo, "has taken a fork.");
	if (!philosopher_dead(philo))
	{
		if (philo->num % 2 != 0)
		{
			if (even_number(philo))
				return ;
		}
		else
		{
			if (odd_number(philo))
				return ;
		}
	}
	if (!philosopher_dead(philo))
		print(philo, "is eating.");
	return ;
}

void	put_forks(t_philo *philo)
{
	if (!philosopher_dead(philo))
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
}

void	*start_philo(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *) vargp;
	philo->eat_count = 0;
	philo->last_eat = 0;
	while (!philo->info->dead)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->info->lock);
		philo->eat_count++;
		philo->last_eat = current_time() - philo->info->init;
		pthread_mutex_unlock(&philo->info->lock);
		ft_usleep(philo->info->time_eat + 20, current_time() - philo->info->init);
		if (!philosopher_dead(philo))
		{
			put_forks(philo);
			print(philo, "is sleeping.");
			ft_usleep(philo->info->time_sleep - 20, \
				current_time() - philo->info->init);
		}
		if (!philosopher_dead(philo))
			print(philo, "is thinking.");
	}
	return (NULL);
}
