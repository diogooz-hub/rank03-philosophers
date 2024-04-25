/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:18:50 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/25 22:02:57 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->mutex);
	if (philo->program->philosopher_dead == 1)
	{
		pthread_mutex_unlock(&philo->program->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->mutex);
	return (0);
}

int	philos_are_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->mutex);
	if (philo->program->all_full == 1)
	{
		pthread_mutex_unlock(&philo->program->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->mutex);
	return (0);
}


int	check_if_all_full(t_data *program)
{
	int	i;

	i = -1;
	while (++i < program->number_of_philos)
	{
		if (program->philosopher[i].number_of_meals != 0)
			return (0);
	}
	program->all_full = 1;
	return (1);
}

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->program->starting_time > philo->time_to_die)
	{
		philo->program->philosopher_dead = 1;
		message_from_monitoring("died", philo);
		return (1);
	}
	else
		return (0);
}

int	check_if_one_is_dead(t_data *program)
{
	int	i;

	i = 0;
	while (i < program->number_of_philos)
	{
		if (check_last_meal(&program->philosopher[i]))
			return (1);
		i++;
	}
	return (0);
}

void	monitoring(t_data *program)
{
	while (1)
	{
		pthread_mutex_lock(&program->mutex);
		if (check_if_one_is_dead(program))
		{
			usleep(200);
			pthread_mutex_unlock(&program->mutex);
			//printf("check1\n");
			return ;
		}
		pthread_mutex_unlock(&program->mutex);
		pthread_mutex_lock(&program->mutex);
		if (check_if_all_full(program))
		{
			usleep(200);
			ft_printf("all full\n");
			pthread_mutex_unlock(&program->mutex);
			//printf("check2\n");
			return ;
		}
		pthread_mutex_unlock(&program->mutex);
		usleep(200);
	}
}