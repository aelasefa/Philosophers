/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:09:32 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:09 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(int ac, char **av, t_input *args)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Incorrect number of arguments\n");
		return (0);
	}
	args->nbr_philo = ft_atoi(av[1]);
	args->die_time = ft_atoi(av[2]);
	args->eat_time = ft_atoi(av[3]);
	args->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		args->count_eat = ft_atoi(av[5]);
	else 
		args->count_eat = -1;
	if (args->nbr_philo <= 0 || args->die_time <= 0 ||
        args->eat_time <= 0 || args->sleep_time <= 0 ||
        (ac == 6 && args->count_eat <= 0)) {
		printf("Error: Arguments must be positive numbers\n");
		return (0);
    }
	return (1);
}
