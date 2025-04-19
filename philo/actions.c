/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:09:59 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/19 18:45:46 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	time_to_die;
	int		dead;

	time_to_die = philo->input->die_time;
	pthread_mutex_lock(&philo->input->last_meal_time_lock);
	dead = (get_time() - philo->last_meal_time > time_to_die);
	pthread_mutex_unlock(&philo->input->last_meal_time_lock);
	return (dead);
}

int	is_terminated(t_philo *philo)
{
	int	nb_iterations;
	int	done;

	nb_iterations = philo->input->count_eat;
	if (nb_iterations < 0)
		return (0);
	done = (philo->meals_eaten >= nb_iterations);
	return (done);
}

int	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	if (check_simulation_end(philo->input) || philo_died(philo))
	{
		release_forks(philo);
		return (0);
	}
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	print_action(philo, "is eating");
	usleep(philo->input->eat_time * 1000);
	release_forks(philo);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->input->sleep_time * 1000);
	return (1);
}

int	philo_think(t_philo *philo)
{
	t_input	*input;
	long	time_to_die;
	long	time_till_death;
	long	time_to_eat;
	long	time_to_sleep;

	input = philo->input;
	if (check_simulation_end(input) || philo_died(philo))
		return (0);
	print_action(philo, "is thinking");
	if (input->nbr_philo % 2 == 0)
		return (1);
	time_to_eat = input->eat_time;
	time_to_sleep = input->sleep_time;
	time_to_die = input->die_time;
	if (time_to_sleep < time_to_eat)
		usleep((time_to_eat - time_to_sleep) * 1000);
	time_till_death = get_time() - philo->last_meal_time;
	if (time_till_death < time_to_die * 0.7)
		usleep(1000);
	return (1);
}
