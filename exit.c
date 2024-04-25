/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:42:07 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/13 00:43:06 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *program)
{
	int	i;

	i = -1;
	while (++i < program->number_of_philos)
		pthread_mutex_destroy(&program->fork_mutex[i]);
	pthread_mutex_destroy(&program->mutex);
}


void	free_program(t_data *program)
{
	destroy_mutexes (program);
	free (program->fork_mutex);
	free (program->philosopher);
	//free (program);
}


void	exit_error(char *s)
{
	ft_printf("%s\n", s);
	exit (1);
}