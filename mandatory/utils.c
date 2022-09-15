/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:38:05 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/15 00:38:09 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	exit(1);
}

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

int	check_args(t_info *info)
{
	if (info->num_philo == -1 || info->time_die == -1 || info->time_eat == -1 || info->time_sleep == -1 || info->num_eat == -1)
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
	(*info)->num_eat = 0;
	if (argc == 6)
		(*info)->num_eat = ft_atoi(argv[5]);
	(*info)->dead = 0;
	if (check_args(*info))
	{
		free(*info);
		return (1);
	}
	(*info)->fork = malloc(sizeof(pthread_mutex_t) * (*info)->num_philo);
	(*info)->philo = malloc(sizeof(t_philo) * (*info)->num_philo);
	if(!((*info)->fork && (*info)->philo))
		return (1);
	while (++i < (*info)->num_philo)
		if (pthread_mutex_init(&(*info)->fork[i], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&(*info)->lock, NULL) != 0)
		return (1);
	printf("here?\n");
	return (0);
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->lock);
	printf("%li ms %i %s\n",current_time() - philo->info->init, philo->num, str);
	pthread_mutex_unlock(&philo->info->lock);
}
