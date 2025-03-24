#ifndef PHILO_H
#define PHLO_H


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
int ft_atoi(char *str);

#endif
