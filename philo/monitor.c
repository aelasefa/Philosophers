/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 00:27:02 by ayelasef          #+#    #+#             */
/*   Updated: 2025/05/28 18:21:14 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_and_handle_death(t_input *input, t_philo *philo)
{
	int	is_checking;

	pthread_mutex_lock(philo->meal_lock);
	is_checking = philo->check;
	pthread_mutex_unlock(philo->meal_lock);
	if (!is_checking && philo_died(philo))
	{
		pthread_mutex_lock(&input->death_lock);
		input->is_dead = 1;
		pthread_mutex_unlock(&input->death_lock);
		pthread_mutex_lock(&input->print_lock);
		printf("%lld %d died\n", get_time() - input->start_time, philo->id);
		pthread_mutex_unlock(&input->print_lock);
		return (1);
	}
	return (0);
}

static int	philos_running(t_input *input)
{
	int	i;
	int	philos_done;

	i = 0;
	philos_done = 0;
	while (i < input->nbr_philo)
	{
		if (is_terminated(&input->philos[i]))
			philos_done++;
		else if (check_and_handle_death(input, &input->philos[i]))
			return (0);
		i++;
	}
	return (philos_done != input->nbr_philo);
}

void	*death_monitor(void *arg)
{
	t_input	*input;

	input = (t_input *)arg;
	while (get_time() < input->start_time)
		usleep(250);
	usleep(input->die_time * 1000);
	while (philos_running(input))
		usleep(500);
	return (NULL);
}
