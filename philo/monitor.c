/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:33:41 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 13:51:36 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_terminated(t_philo *philo)
{
	if (philo->input->count_eat == -1)
		return (0);
	return (philo->meals_eaten >= philo->input->count_eat);
}

int	check_simulation_end(t_input *input)
{
	int	ended;

	pthread_mutex_lock(&input->death_lock);
	ended = input->is_dead;
	pthread_mutex_unlock(&input->death_lock);
	return (ended);
}

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
	int		full_philos;

	input = (t_input *)arg;
	while (!check_simulation_end(input))
	{
		i = 0;
		full_philos = 0;
		while (i < input->nbr_philo)
		{
			if (check_philosopher_death(input, i))
				return (NULL);
			if (is_terminated(&input->philos[i]))
				full_philos++;
			i++;
		}
		if (input->count_eat != -1 && full_philos == input->nbr_philo)
		{
			pthread_mutex_lock(&input->death_lock);
			input->is_dead = 1;
			pthread_mutex_unlock(&input->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
