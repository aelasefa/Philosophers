/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:05:48 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/23 10:07:03 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->input->print_lock);
	if (check_simulation_end(philo->input))
	{
		pthread_mutex_unlock(&philo->input->print_lock);
		return ;
	}
	printf("%lld %d %s\n", get_time() - philo->input->start_time, philo->id,
		action);
	pthread_mutex_unlock(&philo->input->print_lock);
}

void	handle_one_philosopher(t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	print_action(philo, "has taken a fork");
	ft_sleep(philo->input->die_time * 1000, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->input->nbr_philo == 1)
	{
		handle_one_philosopher(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(500);
		if (philo->input->nbr_philo < 100)
			usleep(200);
		if (!philo_eat(philo))
			break ;
		if (is_terminated(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}
