/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:00:00 by                   #+#    #+#             */
/*   Updated: 2025/02/16 14:37:49 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_message(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_message(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->eating);
	print_message(data, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->eating);
	ft_usleep(data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!data->philo_died)
	{
		eating(philo);
		print_message(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_sleep);
		print_message(data, philo->id, "is thinking");
	}
	return (NULL);
}