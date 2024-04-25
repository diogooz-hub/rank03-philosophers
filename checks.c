/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:54:56 by dpaco             #+#    #+#             */
/*   Updated: 2024/04/13 00:45:20 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if ((int)av[i][j] < 48 || (int)av[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_arguments(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	else
	{
		if (!check_digits(ac, av))
		{
			printf("Error: args are not numbers\n");
			return (0);
		}
	}
	return (1);
}
