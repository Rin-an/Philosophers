/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:22:06 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/17 18:40:48 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		id;
	int				num;
	int				eat_count;
	long			last_eat;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	long			init;
	int				total;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	t_philo			*philo;
}	t_info;

int		ft_atoi(char *str);
int		parse_args(t_info **info, int argc, char **argv);
long	current_time(void);
long	time_in_ms(t_info *info);
void	*start_philo(void *vargp);
void	ft_usleep(long duration);
void	print(t_philo *philo, char *str);
void	monitor(t_info *info);
void	destroy_all(t_info *info);
#endif
