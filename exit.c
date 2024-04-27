/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:42:07 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/27 17:30:10 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutexes(t_data *program)
{
	int	i;

	i = -1;
	while (++i < program->number_of_philos)
		pthread_mutex_destroy(&program->fork_mutex[i]);
	free(program->fork_mutex);
}

void	free_program(t_data *program)
{
	destroy_fork_mutexes(program);
	pthread_mutex_destroy(&program->mutex);
	free (program->philosopher);
}
