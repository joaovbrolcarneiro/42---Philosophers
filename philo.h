/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/03/19 15:56:34 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				philo_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	printing;
	t_philo			*philosophers;
}	t_data;

/* init.c */
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);

/* utils.c */
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_message(t_data *data, int id, char *str);
void		ft_usleep(long long time);

/* philo_actions.c */
void		*philosopher_life(void *arg);
void		eating(t_philo *philo);

/* monitor.c */
int			check_death(t_data *data, int i);
void		monitor_philosophers(t_data *data);
int			all_philosophers_ate_enough(t_data *data);

#endif