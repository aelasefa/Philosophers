/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:33:41 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 13:05:17 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_input *input, int i)
{
	long long	time_since_meal;

	pthread_mutex_lock(&input->death_lock);
	time_since_meal = get_time() - input->philos[i].last_meal_time;
	if (time_since_meal > input->die_time)
	{
		pthread_mutex_lock(&input->print_lock);
		printf("%lld %d died\n", get_time() - input->start_time,
			input->philos[i].id);
		input->is_dead = 1;
		pthread_mutex_unlock(&input->print_lock);
		pthread_mutex_unlock(&input->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&input->death_lock);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_input	*input;
	int		i;

	input = (t_input *)arg;
	while (!input->is_dead)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			if (check_philosopher_death(input, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
