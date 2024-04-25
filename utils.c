/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:07:41 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/25 15:28:07 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_from_philo(char *str, t_philo *philosopher)
{
	if (philo_is_dead(philosopher) || philos_are_full(philosopher))
			return ;
	pthread_mutex_lock(&philosopher->program->mutex);
	ft_printf("%d %d %s\n", (get_time() - philosopher->program->starting_time), philosopher->id, str);
	pthread_mutex_unlock(&philosopher->program->mutex);
}

void	message_from_monitoring(char *str, t_philo *philosopher)
{
	ft_printf("%d %d %s\n", (get_time() - philosopher->program->starting_time), philosopher->id, str);
}

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_busy(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}