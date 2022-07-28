#include "philosophers.h"

// int	checkdeath(t_philo *philo)
// {

// }

// int	ft_checkdead(t_data *data)
// {
// 	pthread_mutex_lock(&data->status_m);
// 	if (data->status)
// 	{
// 		pthread_mutex_unlock(&data->status_m);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->status_m);
// 	return (0);
// }

// int	daddy_decides(t_philo *philo)
// {
// 	while (1)
// 	{
// 		if ()
// 	}
// }

int	ft_sleep(t_philo *philo)
{
	int	begin_eat;

	begin_eat = diff_time2(philo->data);
	if (philo->data->tt_die <= philo->data->tt_eat)
	{
		philo->data->alive = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	usleep(philo->data->tt_eat);
	if (diff_time2(philo->data) - begin_eat >= philo->data->tt_eat)
	{
		philo->data->alive = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
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
		// if (ft_sleep(philo))
		// 	return (print_action(philo, DEAD_MSG), 1);
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
		// if (ft_sleep(philo))
		// 	return (print_action(philo, DEAD_MSG), 1);
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
	while (1)
	{
		// philo_is_hungry(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->alive == 1)
			return ((void)pthread_mutex_unlock(&philo->data->lock), NULL);
		pthread_mutex_unlock(&philo->data->lock);
		philo_is_hungry(philo);
		asleep_think(philo);
	}
	return (NULL);
}
