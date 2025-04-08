/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:22:12 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/07 19:27:08 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_input	input;
	int		i;

	if (!parse_input(ac, av, &input))
		return (1);
	if (init_philosophers(&input) || init_mutexes(&input))
	{
		free_input(&input);
		return (1);
	}
		i = 0;
	while (i < input.nbr_philo)
		pthread_create(&input.philos[i].thread, NULL, &routine, &input.philos[i++]);

	pthread_create(&monitor, NULL, &death_monitor, &input);
	pthread_join(monitor, NULL);

	i = 0;
	while (i < input.nbr_philo)
		pthread_join(input.philos[i++].thread, NULL);

	free_input(&input);
	return (0);
	if (start_simulation(&input))
		return (1);
	join_threads(&input);
}
