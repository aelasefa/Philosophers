#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_input 
{
	int nbr_philo;
	int die_time;
	int eat_time;
	int sleep_time;
	int count_eat;

	long long start_time;
	int is_dead;
	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
	pthread_mutex_t death_lock;
	int i;
	struct s_philo *philos;
}		t_input;

typedef struct s_philo
{
	int id;
	pthread_t thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long long last_meal_time;
	int meals_eaten;
	t_input *input;
}	t_philo;
//philo.c
int	parse_input(int ac, char **av, t_input *args);
//philo_utils.c
int ft_atoi(char *str);
long	get_time(void);
void	free_input(t_input *input);
//philo_routine.c
void	*philo_routine(void *args);
//parse.c
int	parse_input(int ac, char **av, t_input *args);
//init.c
int	init_mutexes(t_input *input);
int	init_philosophers(t_input *input);


int	start_simulation(t_input *input);

int	join_threads(t_input *input);
#endif
