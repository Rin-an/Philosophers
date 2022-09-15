/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:17:42 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/15 00:37:00 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	*tp;

	tp = malloc(sizeof(struct timeval));
	if (gettimeofday(tp, NULL))
		ft_error("Error: failed getting time!");
	return ((tp->tv_sec * 1000) + (tp->tv_usec / 1000));
}

void  ft_usleep(int duration, int init)
{
//	usleep((duration - 20) * 1000);
	while (current_time() - init < duration)
	;
}

int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if ((current_time() - philo->info->init) -  philo->last_eat >= philo->info->time_die)
	{
		//printf("time is %li\n", (current_time() - philo->info->init) - philo->last_eat);
		philo->info->dead = 1;
		printf("%li ms %i died\n", current_time() - philo->info->init, philo->num);
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (0);
}

/*void	*start_philo(void *vargp)
{
	t_philo	*philo;
	int	n;

	philo = (t_philo *) vargp;
	n = philo->info->num_philo;
	philo->eat_count = 0;
	philo->last_eat = 0;
//	philo->lfork = 0;
//	philo->rfork = 0;
	while (!philo->info->dead)
	{
		//printf("last eat = %li\n", philo->last_eat);
		if (philo->num % 2 != 0)
		{
		//	pthread_mutex_lock(&philo->fork[philo->num - 1]);
			pthread_mutex_lock(&philo->lfork);
			printf("%li ms %i has taken left fork.\n", current_time() - philo->info->init, philo->num);
			pthread_mutex_lock(&philo->rfork);
			printf("%li ms %i has taken right fork.\n", current_time() - philo->info->init, philo->num);
		}
		else
		{
		//	pthread_mutex_lock(&philo->fork[((philo->num + 1) % n) - 1]);
			pthread_mutex_lock(&philo->rfork);
			printf("%li ms %i has taken right fork.\n", current_time() - philo->info->init, philo->num);
			pthread_mutex_lock(&philo->lfork);
			printf("%li ms %i has taken left fork.\n", current_time() - philo->info->init, philo->num);
		}
		if (philosopher_dead(philo))
		{
			pthread_mutex_lock(&philo->info->print);
			printf("%li ms %i died.\n", current_time() - philo->info->init, philo->num);
			pthread_mutex_unlock(&(philo->info->print));
			return (0);
		}
		if (philo->num % 2 != 0)
		{
			if (pthread_mutex_lock(&philo->rfork))
				return (pthread_mutex_unlock(&philo->lfork), 1);
		}
		printf("%li ms %i is eating.\n", current_time() - philo->info->init, philo->num);
		philo->eat_count++;
		philo->last_eat = current_time() - philo->info->init;
		ft_usleep(philo->info->time_eat, current_time() - philo->info->init);
		pthread_mutex_unlock(&philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
		printf("%li ms %i is sleeping.\n", current_time() - philo->info->init, philo->num);
		ft_usleep(philo->info->time_sleep, current_time() - philo->info->init);
		printf("%li ms %i is thinking.\n", current_time() - philo->info->init, philo->num);
	}
	return (NULL);
}*/

int	main(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (argc == 5 || argc == 6)
	{
		if (argv[1][0] == '0' && argv[1][1] == '\0')
			return (1);
		if (parse_args(&info, argc, argv))
			return (1);
		i = -1;
		info->init = current_time();
		while (++i < info->num_philo)
		{
			info->philo[i].num = i + 1;
			info->philo[i].info = info;
			info->philo[i].fork = info->fork;
			info->philo[i].rfork = info->fork[(i + 1) % info->num_philo];
			info->philo[i].lfork = info->fork[i];
			if (pthread_create(&(info->philo[i].id), NULL, &start_philo, \
				&info->philo[i]))
				return (0);
		}
		i = -1;
		while (++i < info->num_philo)
			pthread_join(info->philo[i].id, NULL);
	/*	pthread_mutex_destroy(info->print);
		i = -1;
		while (++i < info->num_philo)
		{
			free(&info->philo[i]);
			pthread_mutex_destroy(&info->fork[i]);
		}
		pthread_mutex_destroy(info->fork);
		free(info->fork);
		free(info->philo);
		free(info);*/
	}
	else
		printf("Too many arguments or too few arguments!\n");
	return (0);
}
