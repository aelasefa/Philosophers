/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:05:48 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:11 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->input->print_lock);
	timestamp = get_time() - philo->input->start_time;
	if (!philo->input->is_dead)
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->input->print_lock);
}

void	philo_routine_help(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->input->death_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->input->death_lock);
	philo_log(philo, "is eating");
	usleep(philo->input->eat_time * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo_log(philo, "is sleeping");
	usleep(philo->input->sleep_time * 1000);
	philo_log(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(100);
	while (!philo->input->is_dead)
	{
		philo_routine_help(philo);

		if (philo->input->count_eat > 0 &&
			philo->meals_eaten >= philo->input->count_eat)
			break;
	}
	return (NULL);
}
