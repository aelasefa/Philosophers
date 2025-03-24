#include "philo.h"

int	parse_input(int ac, char **av, t_input *args)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Incorrect number of arguments\n");
		return (0);
	}
	
	args->nbr_philo = ft_atoi(av[1]);
	args->die_time = ft_atoi(av[2]);
	args->eat_time = ft_atoi(av[3]);
	args->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		args->count_eat = ft_atoi(av[5]);
	else 
		args->count_eat = -1;
	if (args->nbr_philo <= 0 || args->die_time <= 0 ||
        args->eat_time <= 0 || args->sleep_time <= 0 ||
        (ac == 6 && args->count_eat <= 0)) {
		printf("Error: Arguments must be positive numbers\n");
		return (0);
    }
	return (1);
}

int main(int ac, char **av)
{
	t_input args;

	if (!parse_input(ac, av, &args))
		return (1);
	printf("Parsed arguments:\n");
    printf("Philosophers: %d\n", args.nbr_philo);
    printf("Time to die: %d\n", args.die_time);
    printf("Time to eat: %d\n", args.eat_time);
    printf("Time to sleep: %d\n", args.sleep_time);
    if (args.count_eat != -1)
        printf("Must eat count: %d\n", args.count_eat);
}
