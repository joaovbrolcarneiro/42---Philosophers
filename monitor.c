/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by                   #+#    #+#             */
/*   Updated: 2025/02/16 14:38:11 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->eating);
	if (get_time() - data->philosophers[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->printing);
		printf("%lld %d died\n",
			get_time() - data->start_time, data->philosophers[i].id);
		data->philo_died = 1;
		pthread_mutex_unlock(&data->printing);
		pthread_mutex_unlock(&data->eating);
		return (1);
	}
	pthread_mutex_unlock(&data->eating);
	return (0);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (!data->philo_died)
	{
		i = 0;
		while (i < data->number_of_philosophers && !data->philo_died)
		{
			if (check_death(data, i))
				return ;
			i++;
		}
		usleep(100);
	}
}