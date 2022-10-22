/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:17:42 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/22 10:12:36 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		info->init = current_time();
		create_process(&info);
		//wait_process(info);
		i = -1;
		while (waitpid(0,0,0) != 0)
		{
			printf("i = %i\n", i);
			//waitpid(info->pid[i], 0, 0);
		}
		printf("DID IT EVER EVEN GET HERE???????????\n");
		kill_process(info);
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
