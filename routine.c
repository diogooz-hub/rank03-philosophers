/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:47:16 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/25 15:29:32 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (philo->program->philosopher_dead == 0)
	{
		if (philo_is_dead(philo) || philo->program->number_of_philos == 1)
			return (0);
		philo_takes_fork(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_eating(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
		//printf("all full: %d\n", philo->program->all_full);
	}
	return (0);
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
