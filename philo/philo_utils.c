#include "philo.h"

int	ft_atoi(char *str)
{
	long	result;
	long	last_result;

	int (signe), i;
	i = 0;
	signe = 1;
	result = 0;
	last_result = 0;
	while ((str[i] != '\0' && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (last_result > 2147483647 || last_result < -2147483648)
			return (-1);
		result = result * 10 + str[i] - '0';
		last_result = signe * result;
		i++;
	}
	return (last_result);
}

void	free_input(t_input *input)
{
	int	i;

	if (input->philos)
		free(input->philos);
	if (input->forks)
	{
		i = 0;
		while (i < input->nbr_philo)
			pthread_mutex_destroy(&input->forks[i++]);
		free(input->forks);
	}
	pthread_mutex_destroy(&input->print_lock);
	pthread_mutex_destroy(&input->death_lock);
}

long	get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
