/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:19:40 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/23 23:31:32 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include "libft/headers/libft.h"
#include "libft/headers/get_next_line.h"
#include "libft/headers/ft_printf.h"
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_philo
{
	int					id;
	int					last_meal;
	int					eating;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	pthread_t			thread_id;
	struct s_data		*program;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

typedef struct s_data
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	int					starting_time;
	int					philosopher_dead;
	int					all_full;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*fork_mutex;
	t_philo				*philosopher;
}	t_data;

//checks
int check_arguments(int ac, char **av);

//routine
void	begin_threads(t_data *program);
void	join_threads(t_data *program);

//actions
int  	philo_is_dead(t_philo *philosopher);
int		philo_takes_fork (t_philo *philosopher);
void	philo_is_eating(t_philo *philosopher);
void	philo_is_sleeping(t_philo *philosopher);
void	philo_is_thinking(t_philo *philosopher);
int		philos_are_full(t_philo *philo);

//monitoring
void	monitoring(t_data *program);

//utils
void	ft_busy(int time);
int		get_time(void);
void	exit_error(char *s);
void	free_program(t_data *program);
void	message_from_philo(char *str, t_philo *philosopher);
void	message_from_monitoring(char *str, t_philo *philosopher);

#endif