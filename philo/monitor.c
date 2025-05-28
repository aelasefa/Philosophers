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

static int	philos_running(t_input *input)
{
	int	i;
	int	philos_done;

	philos_done = 0;
	i = 0;
	while (i < input->nbr_philo)
	{
		if (is_terminated(&input->philos[i]))
			philos_done++;
		else
		{
			pthread_mutex_lock(input->philos[i].meal_lock);
			int is_checking = input->philos[i].check;
			pthread_mutex_unlock(input->philos[i].meal_lock);

			if (!is_checking && philo_died(&input->philos[i]))
			{
				pthread_mutex_lock(&input->death_lock);
				input->is_dead = 1;
				pthread_mutex_unlock(&input->death_lock);
				pthread_mutex_lock(&input->print_lock);
				printf("%lld %d died\n", get_time() - input->start_time,
					input->philos[i].id);
				pthread_mutex_unlock(&input->print_lock);

				return (0);
			}
		}
		i++;
	}
	return (philos_done != input->nbr_philo);
}

void	*death_monitor(void *arg)
{
	t_input	*input = (t_input *)arg;

	while (get_time() < input->start_time)
		usleep(250);
	usleep(input->die_time * 1000);
	while (philos_running(input))
		usleep(500);
	return (NULL);
}

