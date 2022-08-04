#include "philosophers.h"

int	is_alive(t_philo *philo)
{
	unsigned long	time;

	if (diff_time2(philo->last_meal, now()) >= philo->data->tt_die * 1000 - philo->data->tt_eat * 1000)
	{
		usleep((philo->data->tt_die * 1000) - philo->data->tt_eat * 1000);
		print_action2(philo, DEAD_MSG);
		return (1);
	}
	else if (diff_time2(philo->last_meal, now()) >= philo->data->tt_die * 1000)
	{
		usleep((philo->data->tt_die * 1000));
		print_action2(philo, DEAD_MSG);
		return (1);
	}
	return (0);
}

int	is_running(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->alive_m);
	status = 0;
	if (is_alive(philo))
	{
		philo->data->alive = 1;
		status = 1;
	}
	else if (philo->data->alive == 1)
		status = 1;
	pthread_mutex_unlock(&philo->data->alive_m);
	return (status);
}

int	philo_is_hungry(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &philo->data->mutex_fork[(philo->id) % philo->data->nb_philo];
	fork2 = &philo->data->mutex_fork[((philo->id - 1)) % philo->data->nb_philo];
	if (philo->id % 2)
	{
		pthread_mutex_lock(fork1);
		print_action(philo, FORK_MSG);
		pthread_mutex_lock(fork2);
		print_action(philo, FORK_MSG);
		print_action(philo, EAT_MSG);
		philo->last_meal = now();
		usleep(1000 * philo->data->tt_eat);
		pthread_mutex_unlock(fork2);
		pthread_mutex_unlock(fork1);
	}
	else
	{
		pthread_mutex_lock(fork1);
		print_action(philo, FORK_MSG);
		pthread_mutex_lock(fork2);
		print_action(philo, FORK_MSG);
		print_action(philo, EAT_MSG);
		philo->last_meal = now();
		usleep(1000 * philo->data->tt_eat);
		pthread_mutex_unlock(fork2);
		pthread_mutex_unlock(fork1);
	}
	return (0);
}

bool	asleep_think(t_philo *philos)
{
	int	time;

	print_action(philos, SLEEP_MSG);
	usleep(philos->data->tt_sleep);
	print_action(philos, THINKING_MSG);
	return (0);
}

void	*routine(void *philos_to_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philos_to_cast;
	if (philo->id % 2)
		usleep(philo->data->tt_eat / 2);
	philo->last_meal = now();
	while (!is_running(philo))
	{
		// pthread_mutex_lock(&philo->data->lock);
		// if (philo->data->alive == 1)
		// 	return ((void)pthread_mutex_unlock(&philo->data->lock), NULL);
		// pthread_mutex_unlock(&philo->data->lock);
		philo_is_hungry(philo);
		asleep_think(philo);
	}
	return (NULL);
}
