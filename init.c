/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by                   #+#    #+#             */
/*   Updated: 2025/02/16 14:41:15 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
    (void) argc;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philo_died = 0;
	if (data->number_of_philosophers < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (1);
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philosophers)
	{
		free(data->forks);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->printing, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->number_of_philosophers;
		data->philosophers[i].data = data;
		i++;
	}
	return (0);
}