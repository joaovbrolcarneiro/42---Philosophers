/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/03/19 15:59:56 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philosophers)
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
	while (i < data->nbr_of_philosophers)
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
	while (i < data->nbr_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

static int	run_simulation(t_data *data)
{
	if (create_threads(data))
	{
		free_data(data);
		return (1);
	}
	monitor_philosophers(data);
	join_threads(data);
	free_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
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
	return (run_simulation(&data));
}
