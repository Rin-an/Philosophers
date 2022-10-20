/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:38:05 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/19 19:41:25 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	r;
	int	i;

	i = 0;
	if (str[i] == '-')
		return (-1);
	r = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (-1);
	if ((long) r > 2147483647)
		return (-1);
	return (r);
}

int	check_args(t_info *info, int argc)
{
	if (info->num_philo == -1 || info->time_die == -1 || \
			info->time_eat == -1 || info->time_sleep == -1 || \
			(argc == 6 && info->num_eat == -1))
		return (1);
	return (0);
}

int	init_thread_sem(t_info **info)
{
	(*info)->forks = sem_open("forks", O_CREAT, (*info)->num_philo);
	(*info)->lock = sem_open("lock", O_CREAT);
	(*info)->philo = malloc(sizeof(t_philo) * (*info)->num_philo);
	if (!(*info)->philo)
		return (1);
	return (0);
}

int	parse_args(t_info **info, int argc, char **argv)
{
	int	i;

	i = -1;
	*info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	(*info)->num_philo = ft_atoi(argv[1]);
	(*info)->time_die = ft_atoi(argv[2]);
	(*info)->time_eat = ft_atoi(argv[3]);
	(*info)->time_sleep = ft_atoi(argv[4]);
	(*info)->total = 0;
	(*info)->num_eat = -1;
	if (argc == 6)
		(*info)->num_eat = ft_atoi(argv[5]);
	if (check_args(*info, argc))
	{
		free(*info);
		return (1);
	}
	if (init_thread_sem(info))
		return (1);
	return (0);
}

void	print(t_philo *philo, char *str)
{
	sem_wait(philo->info->lock);
	printf("%li ms %i %s\n", current_time() - philo->info->init, \
		philo->num, str);
	sem_post(philo->info->lock);
}
