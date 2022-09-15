/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:23:12 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/15 00:47:24 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->num % 2 != 0)
		pthread_mutex_lock(&philo->lfork);
	else
		pthread_mutex_lock(&philo->rfork);
	if (!philosopher_dead(philo))
	{
		if (philo->num % 2 != 0)
		{
			if (pthread_mutex_lock(&philo->rfork))
			{
				pthread_mutex_unlock(&philo->lfork);
				return (0);
			}
			else if (!philosopher_dead(philo))
			  print(philo, "has taken a fork.");
		}
		else
		{
			if (pthread_mutex_lock(&philo->lfork))
			{
				pthread_mutex_unlock(&philo->rfork);
				return (0);
			}
			else if (!philosopher_dead(philo))
			  print(philo, "has taken a fork.");
		}
	}
	if (!philosopher_dead(philo))
		print(philo, "is eating.");
	return (0);
}

void	put_forks(t_philo *philo)
{
	if (!philosopher_dead(philo))
	{
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(&philo->lfork);
	}
}

void    *start_philo(void *vargp)
{
	t_philo *philo;
	int n;

	philo = (t_philo *) vargp;
	n = philo->info->num_philo;
	philo->eat_count = 0;
	philo->last_eat = 0;
	while (!philo->info->dead)
	{
		take_forks(philo);
		philo->eat_count++;
		philo->last_eat = current_time() - philo->info->init;
		ft_usleep(philo->info->time_eat, current_time() - philo->info->init);
		put_forks(philo);
		print(philo, "is sleeping.");
		ft_usleep(philo->info->time_sleep, current_time() - philo->info->init);
		print(philo, "is thinking.");
	}
	return (NULL);
}
