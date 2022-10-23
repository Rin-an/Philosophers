/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:22:06 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/23 16:28:12 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		id;
	int				num;
	int				eat_count;
	long			last_eat;
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
	sem_t			*fork;
	sem_t			*lock;
	t_philo			*philo;
	pid_t			*pid;
}	t_info;

int		ft_atoi(char *str);
int		parse_args(t_info **info, int argc, char **argv);
long	current_time(void);
long	time_in_ms(t_info *info);
void	start_philo(t_philo *philo);
void	ft_usleep(long duration);
void	print(t_philo *philo, char *str);
void	*monitor(void *vargp);
void	destroy_all(t_info *info);
void	create_process(t_info **info);
void	kill_process(t_info *info);
#endif
