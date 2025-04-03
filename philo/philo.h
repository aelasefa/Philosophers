#ifndef PHILO_H
#define PHLO_H

#define MIN_PHILO 2
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
}	t_input;

typedef struct s_philosophers
{
	int id;
	pthread_t thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosophers;

int ft_atoi(char *str);

#endif
