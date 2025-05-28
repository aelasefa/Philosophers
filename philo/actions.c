/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:09:59 by ayelasef          #+#    #+#             */
/*   Updated: 2025/05/28 18:23:27 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_died(t_philo *philo)
{
	int dead;
	long long now;

	now = get_time();
	pthread_mutex_lock(philo->last_meal_time_lock);
	dead = (now - philo->last_meal_time > philo->input->die_time);
	pthread_mutex_unlock(philo->last_meal_time_lock);
	return dead;
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

int philo_eat(t_philo *philo)
{
    if (!take_forks(philo))
        return (0);
    if (check_simulation_end(philo->input) || philo_died(philo))
    {
        release_forks(philo);
        return (0);
    }
    print_action(philo, "is eating");
    pthread_mutex_lock(philo->last_meal_time_lock);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(philo->last_meal_time_lock);
    pthread_mutex_lock(philo->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_sleep(philo->input->eat_time * 1000, philo);
    release_forks(philo);
    return (1);
}

int philo_sleep(t_philo *philo)
{
    if (check_simulation_end(philo->input))
        return 0;

    print_action(philo, "is sleeping");
    ft_sleep(philo->input->sleep_time * 1000, philo);
    return 1;
}

int philo_think(t_philo *philo)
{
    if (check_simulation_end(philo->input) || philo_died(philo))
        return 0;
    print_action(philo, "is thinking");
    if (philo->input->nbr_philo % 2 == 1)
        ft_sleep((philo->input->eat_time / 2) * 1000, philo);

    return 1;
}
