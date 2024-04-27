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
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_arguments(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_printf("Error: wrong number of arguments\n");
		return (1);
	}
	else
	{
		if (check_digits(ac, av))
		{
			ft_printf("Error: invalid args\n");
			return (1);
		}
	}
	return (0);
}
