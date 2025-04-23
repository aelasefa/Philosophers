/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:51:21 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/23 12:30:45 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_simulation_end(t_input *input)
{
	int	ended;

	pthread_mutex_lock(&input->death_lock);
	ended = input->is_dead;
	pthread_mutex_unlock(&input->death_lock);
	return (ended);
}

void	ft_sleep(long long time, t_philo *philo)
{
	long long	start;

	time /= 1000;
	start = get_time();
	while ((get_time() - start) < time)
	{
		if (check_simulation_end(philo->input))
			break ;
		usleep(100);
	}
}
