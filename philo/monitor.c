/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:33:41 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 10:33:44 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_input *input = (t_input *)arg;
	int		i;

	while (!input->is_dead)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			pthread_mutex_lock(&input->death_lock);
			long long time_since_meal = get_time() - input->philos[i].last_meal_time;
			if (time_since_meal > input->die_time)
			{
				pthread_mutex_lock(&input->print_lock);
				printf("%lld %d died\n", get_time() - input->start_time, input->philos[i].id);
				input->is_dead = 1;
				pthread_mutex_unlock(&input->print_lock);
				pthread_mutex_unlock(&input->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&input->death_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

