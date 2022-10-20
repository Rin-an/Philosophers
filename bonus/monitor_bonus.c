/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:57:52 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/20 01:12:53 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *) vargp;
	while (1)
	{
		if (philo->eat_count == philo->info->num_eat)
			return (NULL);
		if (time_in_ms(philo->info) - philo->last_eat > philo->info->time_die)
		{	
			philo->dead = 1;
			sem_wait(philo->info->lock);
			printf("%li ms %i died.\n", current_time() - philo->info->init, philo->num);
			kill_process(philo->info);
			destroy_all(philo->info);
			exit(1);
		}
		usleep(50);
	}
	return (NULL);
}
