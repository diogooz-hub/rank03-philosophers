/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:42:07 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/27 15:35:46 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//fazer verificações de as coisas existem antes de destruir ou dar free


void	destroy_fork_mutexes(t_data *program)
{
	int	i;

	i = -1;
	while (++i < program->number_of_philos)
		pthread_mutex_destroy(&program->fork_mutex[i]);
}


void	free_program(t_data *program)
{
	//if (program->mutex)
	//	pthread_mutex_destroy(&program->mutex);
	if (program->fork_mutex)
	{
		destroy_fork_mutexes(program);
		free (program->fork_mutex);
	}
	if (program->philosopher)
		free (program->philosopher);
}


int	exit_error(char *s, t_data *program)
{
	free_program(program);
	ft_printf("%s\n", s);
	return (1);
}