/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:02:58 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/25 15:09:30 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	philo_takes_fork (t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	message_from_philo ("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (pthread_mutex_unlock(philo->right_fork));
		message_from_philo ("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (pthread_mutex_unlock(philo->left_fork));
		message_from_philo ("has taken a fork", philo);
	}
	return (0);
}
*/

int philo_takes_fork(t_philo *philo) {
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // Determine which fork to pick up first based on philosopher's ID
    if (philo->id % 2 == 0) {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    } else {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }

    // Attempt to acquire the first fork
    if (pthread_mutex_lock(first_fork) != 0) {
        // Failed to acquire the first fork
        return 1; // Indicate failure
    }

    // Successfully acquired the first fork, print message
    message_from_philo("has taken a fork", philo);

    // Attempt to acquire the second fork
    if (pthread_mutex_lock(second_fork) != 0) {
        // Failed to acquire the second fork, release the first fork
        pthread_mutex_unlock(first_fork);
        return 1; // Indicate failure
    }

    // Successfully acquired both forks, print message
    message_from_philo("has taken a fork", philo);

    // Both forks acquired successfully
    return 0; // Indicate success
}

void	philo_is_eating(t_philo *philo)
{
	message_from_philo("is eating", philo);
	pthread_mutex_lock(&philo->program->mutex);
	philo->last_meal = get_time() - philo->program->starting_time;
	philo->time_to_die = philo->last_meal + philo->program->time_to_die;
	pthread_mutex_unlock(&philo->program->mutex);
	ft_busy(philo->time_to_eat);
	if (philo->number_of_meals != -1)
		philo->number_of_meals--;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_sleeping(t_philo *philo)
{
	message_from_philo("is sleeping", philo);
	//pthread_mutex_lock(&philo->program->mutex);
	ft_busy(philo->time_to_sleep);
	//pthread_mutex_unlock(&philo->program->mutex);
}

void	philo_is_thinking(t_philo *philo)
{
	message_from_philo("is thinking", philo);
}