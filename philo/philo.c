/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:22:12 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 12:14:24 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creat_thread(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_create(&input->philos[i].thread, NULL, &philo_routine,
			&input->philos[i]);
		input->philos[i].last_meal_time = input->start_time;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_input		input;
	int			i;
	pthread_t	monitor;

	if (!parse_input(ac, av, &input))
		return (1);
	if (init_mutexes(&input) || init_philosophers(&input))
	{
		printf("Error : init failed\n");
		return (1);
	}
	if (input.count_eat != 0)
	{
		creat_thread(&input);
		pthread_create(&monitor, NULL, &death_monitor, &input);
		pthread_join(monitor, NULL);
		i = 0;
		while (i < input.nbr_philo)
			pthread_join(input.philos[i++].thread, NULL);
	}
	free_input(&input);
	return (0);
}
