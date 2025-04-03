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

void think(int id) 
{
    printf("Philosopher %d is thinking...\n", id);
    usleep(1000000);
}

void eat(int id) 
{
    printf("Philosopher %d is eating...\n", id);
    usleep(1000000);
}

void sleep_philosopher(int id) 
{
    printf("Philosopher %d is sleeping...\n", id);
    usleep(1000000);
}

void	*philo_routine(void *args)
{
	t_philosophers *philo = (t_philosophers *)args;
	while (1)
	{
		think(philo->id);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		eat(philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep(philo->id);
	}
	return (NULL);
}
t_philosopher *philosophers;
pthread_mutex_t *forks;
int main(int ac, char **av)
{
	t_input args;
	t_philosophers philo;

	if (!parse_input(ac, av, &args))
		return (1);
       int	i;
       int	n;

       n = atoi(av[1]);
       if (n < MIN_PHILO)
       {
	       printf("Error: You must have at least 2 philosophers.\n");
	       return 1;
       }
       forks = malloc(sizeof(pthread_mutex_t) * n);
       philosophers = malloc(sizeof(t_philosopher) * N);
       if (forks == NULL || philosophers == NULL) 
       {
        	printf("Error: Memory allocation failed.\n");
        	return 1;
       }
       i = 0;
       while (i < n)
       {
	       pthread_mutex_init(&forks[i], NULL);
	       i++;
       }
       i = 0;
       while (i < n)
       {
	       philo[i].id = i;
	       philo[i].left_fork = &forks[i];
	       philo[i].right_fork = &forks[(i + 1) % n];
	       pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
       }
       i = 0;
       while (i < n)
       {
	       pthread_join(philo[i].thread, NULL);
	       i++;
       }
       i = 0;
       while (i < n)
       {
	       pthread_mutex_destroy(&forks[i]);
	       i++;
       }
       free(forks);
       free(philosophers);
       return (0);
}
