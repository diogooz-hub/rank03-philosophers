/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:18:58 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/23 23:31:56 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philos(t_data *program)
{
	int i;

	program->philosopher = malloc(sizeof(t_philo) * program->number_of_philos);
	if (!(program->philosopher))
		return(0);
	i = 0;
	while (i < program->number_of_philos)
	{
		program->philosopher[i].id = i + 1;
		program->philosopher[i].last_meal = 0;
		program->philosopher[i].eating = 0;
		program->philosopher[i].time_to_die = program->time_to_die;
		program->philosopher[i].time_to_sleep = program->time_to_sleep;
		program->philosopher[i].time_to_eat = program->time_to_eat;
		program->philosopher[i].number_of_meals = program->number_of_meals;
		program->philosopher[i].left_fork = &program->fork_mutex[i];
		program->philosopher[i].right_fork = &program->fork_mutex[(i + 1) % program->number_of_philos];
		program->philosopher[i].program = program;
		i++;
	}
	return (1);
}

int init_mutexes(t_data *program)
{
	int	i;

	program->fork_mutex = malloc(sizeof(pthread_mutex_t) * program->number_of_philos);
	if (!program->fork_mutex)
		return (1);
	i = -1;
	while (++i < program->number_of_philos)
	{
		if (pthread_mutex_init(&program->fork_mutex[i], NULL))
			exit_error("Error creating fork mutex");
	}
	if (pthread_mutex_init(&program->mutex, NULL))
		exit_error("Error creating program mutex");
	return (0);
}

int	init_structs(t_data *program, char **av)
{
	program->number_of_philos = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		program->number_of_meals = ft_atoi(av[5]);
	else
		program->number_of_meals = -1;
	program->philosopher_dead = 0;
	program->all_full = 0;
	if (init_mutexes(program))
		return (1);
	if (init_philos(program))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	program;

	if (check_arguments(ac, av))
	{
		if (init_structs(&program, av))
		{
			//printf("--call begin threads on main\n");
			begin_threads(&program);
			//printf("call monitoring threads on main\n");
			monitoring(&program);
			//printf("--call join threads on main\n");
			join_threads(&program);
			//printf("--call free on main\n");
			free_program(&program);
		}
	return (0);
	}
}