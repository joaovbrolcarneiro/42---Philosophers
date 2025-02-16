/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by                   #+#    #+#             */
/*   Updated: 2025/02/16 14:37:29 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->printing);
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].last_meal = data->start_time;
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_life, &(data->philosophers[i])))
			return (1);
		i++;
	}
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	if (init_mutexes(&data))
	{
		free_data(&data);
		return (1);
	}
	if (init_philosophers(&data))
	{
		free_data(&data);
		return (1);
	}
	if (create_threads(&data))
	{
		free_data(&data);
		return (1);
	}
	monitor_philosophers(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}