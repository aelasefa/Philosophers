/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:25 by ayelasef          #+#    #+#             */
/*   Updated: 2025/04/09 12:22:27 by ayelasef         ###   ########.fr       */
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
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	struct s_philo	*philos;
}					t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long long		last_meal_time;
	int				meals_eaten;
	t_input			*input;
}					t_philo;
// philo_utils.c
int					ft_atoi(char *str);
long				get_time(void);
void				free_input(t_input *input);
// philo_routine.c
void	*philo_routine(void *arg);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
void	take_forks(t_philo *philo);
void	print_action(t_philo *philo, const char *action);
// parse.c
int					parse_input(int ac, char **av, t_input *args);
// init.c
int					init_mutexes(t_input *input);
int					init_philosophers(t_input *input);
//monitor.c
int	is_terminated(t_philo *philo);
void				*death_monitor(void *arg);
int	check_simulation_end(t_input *input);
int					start_simulation(t_input *input);
#endif
