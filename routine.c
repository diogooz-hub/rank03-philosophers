/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:47:16 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/27 12:13:51 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->program->number_of_philos == 1)
	{
		handle_one_philo(philo);
		return (NULL);		
	}
	if (philo->id % 2 == 0)
		ft_busy(philo->time_to_eat - 10);
	while (!stop_threds(philo))
	{
		if (stop_threds(philo))
			break ;
		if (philo_takes_fork(philo))
			break ;
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
		if (pthread_join(program->philosopher[i].thread_id, NULL) != 0)
		{
			free_program(program);
			return ;
		}
	}
}

void	begin_threads(t_data *program)
{
	int	i;

	i = -1;
	program->starting_time = get_time();
	while (++i < program->number_of_philos)
	{
		if (pthread_create(&program->philosopher[i].thread_id, NULL, 
				&routine, (void *)&program->philosopher[i]) != 0)
		{
			free_program(program);
			return ;
		}
	}
}
