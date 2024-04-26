/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:47:16 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/26 19:48:32 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (!stop_threds(philo))
	{
		if (philo->program->number_of_philos == 1 || stop_threds(philo))
			break ;
		philo_takes_fork(philo);
		philo_is_eating(philo);
		if (stop_threds(philo))
			break ;
		philo_is_sleeping(philo);
		if (stop_threds(philo))
			break ;
		philo_is_thinking(philo);
	}
	return (NULL);
}

void	join_threads(t_data *program)
{
	int	i;

	i = -1;
	while (++i < program->number_of_philos)
	{
		if (pthread_join(program->philosopher[i].thread_id, NULL))
			exit_error("error joining thread");
	}
}

void	begin_threads(t_data *program)
{
	int	i;

	i = -1;
	program->starting_time = get_time();
	while (++i < program->number_of_philos)
	{
		if (pthread_create(&program->philosopher[i].thread_id, NULL, &routine, (void *)&program->philosopher[i]))
			exit_error("error creating thread");
	}
}
