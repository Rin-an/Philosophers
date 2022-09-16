/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:17:42 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/16 11:59:01 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	*tp;

	tp = malloc(sizeof(struct timeval));
	gettimeofday(tp, NULL);
	return ((tp->tv_sec * 1000) + (tp->tv_usec / 1000));
}

void  ft_usleep(int duration, int init)
{
	usleep((duration - 20) * 1000);
	while (current_time() - init < duration)
	;
}

int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	/*if ((current_time() - philo->info->init) -  philo->last_eat >= philo->info->time_die)
	{
		philo->info->dead = 1;
		printf("%li ms %i died\n", current_time() - philo->info->init, philo->num);
		usleep(100);
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}*/
	if (philo->info->dead)
	{
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (0);
}

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
			info->philo[i].rfork = malloc(sizeof(pthread_mutex_t));
			info->philo[i].rfork = &info->fork[(i + 1) % info->num_philo];
			info->philo[i].lfork = malloc(sizeof(pthread_mutex_t));
			info->philo[i].lfork = &info->fork[i];
			if (pthread_create(&(info->philo[i].id), NULL, &start_philo, \
				&info->philo[i]))
				return (0);
		}
		/*i = -1;
		while (++i < info->num_philo)
			pthread_join(info->philo[i].id, NULL);*/
		monitor(info);
		/*i = -1;
		while (++i < info->num_philo)
			pthread_join(info->philo[i].id, NULL);*/
	}
	else
		printf("Too many arguments or too few arguments!\n");
	return (0);
}
