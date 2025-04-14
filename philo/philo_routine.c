/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:05:48 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 12:18:28 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->input->print_lock);
	if (!check_simulation_end(philo->input))
		printf("%lld %d %s\n",
			get_time() - philo->input->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->input->print_lock);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
	}
	else 
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->death_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->input->death_lock);
	print_action(philo, "is eating");
	usleep(philo->input->eat_time * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);

	while (!check_simulation_end(philo->input))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		print_action(philo, "is sleeping");
		usleep(philo->input->sleep_time * 1000);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
