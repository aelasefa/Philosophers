/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:22:12 by ayelasef          #+#    #+#             */
/*   Updated: 2025/05/28 17:52:42 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void create_threads(t_input *input)
{
	int i;

	i = 0;
	while (i < input->nbr_philo)
	{
		input->philos[i].last_meal_time = input->start_time;
		if (pthread_create(&input->philos[i].thread, NULL, philo_routine,
			&input->philos[i]) != 0)
			printf("Error: Failed to create thread for philosopher %d\n", i + 1);
		i++;
	}
}

int main(int ac, char **av)
{
	t_input input;
	int i;
	pthread_t monitor;
	memset(&input, 0, sizeof(t_input));
	if (!parse_input(ac, av, &input))
	{
		printf("Error: Invalid input\n");
		return 1;
	}
	if (init_mutexes(&input) || init_philosophers(&input))
	{
		printf("Error: Initialization failed\n");
		free_input(&input);
		return 1;
	}
	if (input.count_eat != 0)
	{
		create_threads(&input);

		if (pthread_create(&monitor, NULL, death_monitor, &input) != 0)
			printf("Error: Failed to create monitor thread\n");
		pthread_join(monitor, NULL);
		i = 0;
		while (i < input.nbr_philo)
			pthread_join(input.philos[i++].thread, NULL);
	}
	free_input(&input);
	return 0;
}

