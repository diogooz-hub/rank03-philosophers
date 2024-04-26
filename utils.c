/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:07:41 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/26 19:50:24 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_from_philo(char *str, t_philo *philosopher)
{
	if (stop_threds(philosopher))
		return ;
	pthread_mutex_lock(&philosopher->program->mutex);
	ft_printf("%d %d %s\n", (get_time() - philosopher->program->starting_time), philosopher->id, str);
	pthread_mutex_unlock(&philosopher->program->mutex);
}

void	message_from_monitoring(char *str, t_philo *philosopher)
{
	ft_printf("%d %d %s\n", (get_time() - philosopher->program->starting_time), philosopher->id, str);
}


u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}


void	ft_busy(uint64_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

