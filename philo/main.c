/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:05:11 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/19 18:56:20 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_philosophers(t_input *input)
{
	t_philo	*philo;
	int						i;

	i = 0;
	while (i < input->nbr_philo)
	{
		philo = &input->philos[i];
		if (pthread_create(&input->philos[i].thread, NULL, &philo_routine, philo ) != 0)
		{
			printf("[ERROR] Philo %d failed to create thread\n", i + 1);
			return (i);
		}
		i++;
	}
	return (i);
}

void join_philosophers(t_input *input, int nb_philos)
{
	int i = 0;
	while (i < nb_philos)
	{
		pthread_join(input->philos[i].thread, NULL);
		i++;
	}
}

void simulation_start(t_input *input)
{
	pthread_t monitor_tid;
	input->start_time = get_time();
	if (pthread_create(&monitor_tid, NULL, death_monitor, input) != 0)
	{
		printf("[ERROR] Monitor thread creation failed\n");
		return ;
	}
	int nb_started = start_philosophers(input);
	pthread_join(monitor_tid, NULL);
	join_philosophers(input, nb_started);
}

int main(int ac, char **av)
{
	t_input	input;

	if (!parse_input(ac, av, &input))
		return (1);
	if (input.count_eat != 0)
		simulation_start(&input);
	free_input(&input);
	return (0);
}

