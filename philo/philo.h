/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:25 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/19 18:57:49 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_input
{
	int				nbr_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				count_eat;
	long long		start_time;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	last_meal_time_lock;
	pthread_mutex_t	meals_eaten_lock;
	struct s_philo	*philos;
}					t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	long long		last_meal_time;
	int				meals_eaten;
	t_input			*input;
}					t_philo;
// philo_utils.c
int					ft_atoi(char *str);
long				get_time(void);
void				free_input(t_input *input);
int					check_simulation_end(t_input *input);
void				ft_sleep(long long time);
// philo_routine.c
void				*philo_routine(void *arg);
void				eat(t_philo *philo);
void				print_action(t_philo *philo, char *action);
void				handle_one_philosopher(t_philo *philo);
// parse.c
int					parse_input(int ac, char **av, t_input *args);
// init.c
int					init_mutexes(t_input *input);
int					init_philosophers(t_input *input);
// monitor.c
int					is_terminated(t_philo *philo);
void				*death_monitor(void *arg);
int					start_simulation(t_input *input);
// routine.c
int					philo_sleep(t_philo *philo);
int					philo_eat(t_philo *philo);
int					philo_think(t_philo *philo);
int					check_philo_died(t_philo *philo);
// lock_forks.c
int					take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
// actions.c

int					philo_died(t_philo *philo);
#endif
