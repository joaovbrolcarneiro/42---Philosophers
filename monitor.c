/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/03/19 19:53:51 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, int i)
{
	long long	now;

	pthread_mutex_lock(&data->eating);
	now = get_time();
	if (now - data->philosophers[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->printing);
		if (!data->philo_died)
		{
			printf("%lld %d died\n", now - data->start_time, 
				data->philosophers[i].id);
			data->philo_died = 1;
		}
		pthread_mutex_unlock(&data->printing);
		pthread_mutex_unlock(&data->eating);
		return (1);
	}
	pthread_mutex_unlock(&data->eating);
	return (0);
}

int	all_philosophers_ate_enough(t_data *data)
{
	int	i;
	int	finished;

	if (data->meals_required < 0)
		return (0);
	i = 0;
	finished = 1;
	while (i < data->nbr_of_philosophers)
	{
		pthread_mutex_lock(&data->eating);
		if (data->philosophers[i].meals_eaten < data->meals_required)
			finished = 0;
		pthread_mutex_unlock(&data->eating);
		if (!finished)
			break ;
		i++;
	}
	return (finished);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (!data->philo_died)
	{
		i = 0;
		if (all_philosophers_ate_enough(data))
		{
			pthread_mutex_lock(&data->printing);
			data->philo_died = 1;
			pthread_mutex_unlock(&data->printing);
			return ;
		}
		while (i < data->nbr_of_philosophers && !data->philo_died)
		{
			if (check_death(data, i))
				return ;
			i++;
		}
		usleep(100);
	}
}
