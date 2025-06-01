/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:10:35 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/19 19:05:37 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutexes(t_input *input)
{
	int i;

	input->forks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	input->meal_locks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	input->meals_eaten_locks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	input->last_meal_time_locks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);

	if (!input->forks || !input->meal_locks || !input->meals_eaten_locks || !input->last_meal_time_locks)
		return (1);

	i = 0;
	while (i < input->nbr_philo)
	{
		if (pthread_mutex_init(&input->last_meal_time_locks[i], NULL))
			return (1);
		if (pthread_mutex_init(&input->forks[i], NULL))
			return (1);
		if (pthread_mutex_init(&input->meal_locks[i], NULL))
			return (1);
		if (pthread_mutex_init(&input->meals_eaten_locks[i], NULL))
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
		t_philo *philo = &input->philos[i];
		philo->id = i + 1;
		philo->input = input;
		philo->meals_eaten = 0;
		philo->check = 0;
		philo->last_meal_time = input->start_time;
		philo->l_fork = &input->forks[i];
		philo->r_fork = &input->forks[(i + 1) % input->nbr_philo];
		input->philos[i].last_meal_time_lock = &input->last_meal_time_locks[i];
		philo->meal_lock = &input->meal_locks[i];
		i++;
	}
	return (0);
}

