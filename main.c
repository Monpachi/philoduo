#include "philosophers.h"

void	print_action(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lums	| %d = %s\n", diff_time2(philo->data), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_print);
}


int	philo_is_hungry(t_philo *philo)
{
	pthread_mutex_t	*fork1 = &philo->data->mutex_fork[(philo->id) % philo->data->nb_philo];
	pthread_mutex_t	*fork2 = &philo->data->mutex_fork[((philo->id - 1)) % philo->data->nb_philo];
	if (philo->id % 2)
	{
		pthread_mutex_lock(fork1);
		print_action(philo, FORK_MSG);
		pthread_mutex_lock(fork2);
		print_action(philo, FORK_MSG);
		print_action(philo, EAT_MSG);
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
		usleep(1000 * philo->data->tt_eat);
		pthread_mutex_unlock(fork2);
		pthread_mutex_unlock(fork1);
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb <= 0 || size <= 0 || nmemb > 4294967295 || size > 4294967295)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr)
		memset(ptr, 0, nmemb * size);
	return (ptr);
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
		philo_is_hungry(philo);
		asleep_think(philo);
	}
	return (NULL);
}

int	philo_can_live(t_param_philo *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_t = get_time(data);
	while (i < data->nb_philo)
	{
		pthread_create(&(philos[i].thread_id), NULL, &routine, philos + i);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}


int main(int argc, char **argv)
{
	t_param_philo	data;
	t_philo			*philos;

	if (init_data(&data))
		return (0);
	if (init_mutex(&data))
		return (0);
	philos = malloc(sizeof(t_philo) * (data.nb_philo + 1));
	if (!philos)
		return (destroy_mutex(&data, data.nb_philo - 1, 1), 0);
	init_tab_philo(philos, &data);
	// if (data.nb_philo == 1)
	// 	routine_solo(philos);
	// ICI A VOIR POUR FAIRE CONTINUER
	while (philo_can_live(&data, philos))
	// philo_can_live(&data, philos);

	return (0);
}
