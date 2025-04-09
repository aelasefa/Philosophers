/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:10:35 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 11:48:28 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_input *input)
{
	int	i;

	input->forks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	if (!input->forks)
		return (1);
	i = 0;
	while (i < input->nbr_philo)
	{
		if (pthread_mutex_init(&input->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&input->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&input->death_lock, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_input *input)
{
	int	i;

	input->philos = malloc(sizeof(t_philo) * input->nbr_philo);
	if (!input->philos)
		return (1);
	input->start_time = get_time();
	input->is_dead = 0;
	i = 0;
	while (i < input->nbr_philo)
	{
		input->philos[i].id = i + 1;
		input->philos[i].l_fork = &input->forks[i];
		input->philos[i].r_fork = &input->forks[(i + 1) % input->nbr_philo];
		input->philos[i].last_meal_time = input->start_time;
		input->philos[i].meals_eaten = 0;
		input->philos[i].input = input;
		i++;
	}
	return (0);
}
