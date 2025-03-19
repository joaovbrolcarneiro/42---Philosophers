/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:02:38 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/03/19 19:53:28 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_message(data, philo->id, "has taken a fork");
	ft_usleep(data->time_to_die);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

static void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_message(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_message(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_message(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_message(data, philo->id, "has taken a fork");
	}
}

static void	take_forks_and_eat(t_philo *philo, t_data *data)
{
	take_forks(philo, data);
	pthread_mutex_lock(&data->eating);
	print_message(data, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->eating);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&data->eating);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->eating);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	}
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nbr_of_philosophers == 1)
	{
		handle_single_philo(philo, data);
		return ;
	}
	take_forks_and_eat(philo, data);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		died;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	died = 0;
	while (1)
	{
		pthread_mutex_lock(&data->printing);
		died = data->philo_died;
		pthread_mutex_unlock(&data->printing);
		if (died)
			break ;
		eating(philo);
		if (data->nbr_of_philosophers == 1)
			break ;
		print_message(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_sleep);
		print_message(data, philo->id, "is thinking");
		usleep(100);
	}
	return (NULL);
}
