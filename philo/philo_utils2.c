/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:51:21 by ayelasef          #+#    #+#             */
/*   Updated: 2025/05/28 19:06:13 by ayelasef         ###   ########.fr       */
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

int	check_argument(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
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

void	free_input(t_input *input)
{
	int	i;

	if (!input)
		return ;
	if (input->philos)
		free(input->philos);
	if (input->forks && input->meal_locks && input->meals_eaten_locks
		&& input->last_meal_time_locks)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			pthread_mutex_destroy(&input->forks[i]);
			pthread_mutex_destroy(&input->meal_locks[i]);
			pthread_mutex_destroy(&input->meals_eaten_locks[i]);
			pthread_mutex_destroy(&input->last_meal_time_locks[i]);
			i++;
		}
		free(input->forks);
		free(input->meal_locks);
		free(input->meals_eaten_locks);
		free(input->last_meal_time_locks);
	}
	pthread_mutex_destroy(&input->print_lock);
	pthread_mutex_destroy(&input->death_lock);
}
