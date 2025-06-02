/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:09 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/23 10:06:56 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
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

int	ft_atoi(char *str)
{
	long	result;

	int (signe), i;
	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] != '\0' && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	if (!check_argument(str))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * signe > 2147483647 || result * signe < -2147483648)
			return (-1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
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
