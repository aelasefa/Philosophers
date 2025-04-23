/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:06:06 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/23 10:06:08 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_single_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (check_simulation_end(philo->input))
		return (0);
	pthread_mutex_lock(fork);
	if (check_simulation_end(philo->input))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_action(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->id % 2 != 0)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	if (!lock_single_fork(philo, first))
		return (0);
	if (philo->input->nbr_philo == 1)
	{
		ft_sleep(philo->input->die_time * 1000, philo);
		return (0);
	}
	if (!lock_single_fork(philo, second))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
