/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:22:06 by ssadiki           #+#    #+#             */
/*   Updated: 2022/09/15 00:35:39 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		id;
	int				num;
	int				eat_count;
	long			last_eat;
	bool			is_eating;
	bool			is_thinking;
	bool			is_sleeping;
	pthread_mutex_t	rfork;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*fork;
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
	int				dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	t_philo			*philo;
}	t_info;

int		ft_atoi(char *str);
void	ft_error(char *msg);
int		parse_args(t_info **info, int argc, char **argv);
long	current_time(void);
void	*start_philo(void *vargp);
void	ft_usleep(int duration, int init);
int		philosopher_dead(t_philo *philo);
void	print(t_philo *philo, char *str);
#endif
