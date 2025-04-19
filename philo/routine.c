#include "philo.h"

int check_philo_died(t_philo *philo)
{
	long long time_to_die;
	int dead;

	time_to_die = philo->input->die_time;
	pthread_mutex_lock(&philo->input->last_meal_time_lock);
	dead = ((get_time() - philo->last_meal_time) > time_to_die);
	pthread_mutex_unlock(&philo->input->last_meal_time_lock);
	return (dead);
}

int is_terminated(t_philo *philo)
{
	int required_meals;
	int done;

	required_meals = philo->input->count_eat;
	if (required_meals < 0)
		return (0);
	done = (philo->meals_eaten >= required_meals);
	return (done);
}

int philo_eat(t_philo *philo)
{
	/*if (!philo)*/
	/*	return (0);*/
	take_forks(philo);
	if (check_simulation_end(philo->input) || check_philo_died(philo))
	{
		release_forks(philo);
		return (0);
	}
	pthread_mutex_lock(&philo->input->last_meal_time_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->input->last_meal_time_lock);
	philo->meals_eaten++;
	print_action(philo, "is eating");
	usleep(philo->input->eat_time * 1000);
	release_forks(philo);
	return (1);
}

int philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->input->sleep_time * 1000);
	return (1);
}

int philo_think(t_philo *philo)
{
	long time_to_die = philo->input->die_time;
	long time_to_eat = philo->input->eat_time;
	long time_to_sleep = philo->input->sleep_time;
	long time_since_meal = get_time() - philo->last_meal_time;

	if (check_simulation_end(philo->input) || check_philo_died(philo))
		return (0);
	print_action(philo, "is thinking");
	if (philo->input->nbr_philo % 2 == 0)
		return (1);
	if (time_to_sleep < time_to_eat)
		usleep((time_to_eat - time_to_sleep) * 1000);
	if (time_since_meal < time_to_die * 0.7)
		usleep(1000);
	return (1);
}

