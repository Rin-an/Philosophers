/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:17:42 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/20 15:34:12 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	ft_usleep(long duration)
{
	while (current_time() < duration)
		usleep(100);
}

long	time_in_ms(t_info *info)
{
	return (current_time() - info->init);
}

int	init_philo(t_info **info)
{
	int	i;

	i = -1;
	while (++i < (*info)->num_philo)
	{
		(*info)->philo[i].num = i + 1;
		(*info)->philo[i].info = *info;
		(*info)->philo[i].lfork = &(*info)->fork[i];
		(*info)->philo[i].rfork = &(*info)->fork[(i + 1) % (*info)->num_philo];
		if (pthread_create(&((*info)->philo[i].id), NULL, &start_philo, \
					&((*info)->philo[i])))
			return (1);
		usleep(100);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc == 5 || argc == 6)
	{
		if (argv[1][0] == '0' && argv[1][1] == '\0')
			return (1);
		if (parse_args(&info, argc, argv))
			return (1);
		info->init = current_time();
		if (init_philo(&info))
			return (1);
		monitor(info);
		destroy_all(info);
	}
	else
	{
		printf("Too many arguments or too few arguments!\n");
		printf("./philo time_to_die time_to_eat time_to_sleep"
			" [number_must_eat]\n");
		printf("Example: ./philo 4 100 200 200 2\n");
	}
	return (0);
}
