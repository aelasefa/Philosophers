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
