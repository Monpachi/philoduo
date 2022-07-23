#include "philosophers.h"

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

void	*routine_solo(t_philo *philos)
{
	t_philo			*blaise_pascal;
	unsigned long	time;


	blaise_pascal = philos;
	blaise_pascal->start_t = get_time(philos);
	usleep(philos->data->tt_die);
	time = diff_time(philos) - philos->start_t;
	printf("%ld ms	| \033[0;31mphilo 1 died 💀 \n\033[0m", time);
	return (NULL);
}

// void	print_action(t_philo *philos, char *s)
// {
// 	pthread_mutex_lock(philos.print_mutex);
// 	printf("%d	| %s\n", philos->philo_id, s);
// 	pthread_mutex_unlock(print_mutex);
// }

int	can_lock(t_philo *philos)
{
	int	i;

	i = philos->id - 1;
	if (philos->id == philos->data->nb_philo)
	{
		if (philos->data->fork_state[i] == 0 && philos->data->fork_state[0] == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (philos->data->fork_state[i] == 0 && philos->data->fork_state[i + 1] == 0)
			return (1);
		else
			return (0);
	}
}

int	philo_is_hungry(t_philo *philos)
{
	int	time;
	int	i;

	i = philos->id - 1;
	if (can_lock(philos) == 0)
		return (1);
	// if (philos->id % 2 == 1)
	// 	usleep(philos->data->tt_die / 2);
	lock_state(philos, i);
	unlock_state(philos, i);
	time = diff_time(philos) - philos->start_t;
	lock_fork(philos, i);
	printf("%dms	| %d = %s\n", time, philos->id, FORK_MSG);
	printf("%dms	| %d = %s\n", time, philos->id, FORK_MSG);
	printf("%dms	| %d = %s\n", time, philos->id, EAT_MSG);
	change_state(philos, i);
	usleep(philos->data->tt_eat * 1000);
	unlock_fork(philos, i);
	return (0);
}

void	*routine(void *philos_to_cast)
{
	t_philo	*philo;

	philo = (t_philo *) philos_to_cast;
	philo->start_t = get_time(philo);
	//eat
	// if (philo->id % 2 == 0)
	// 	usleep(philo->data->tt_die / 2);
	if (philo_is_hungry(philo))
		printf("%lums	| %d can't eat SHIT\n", diff_time(philo) - philo->start_t, philo->id);
	//sleep
	//think;
	return (NULL);
}


void	philo_can_live(t_param_philo *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&(philos[i].thread_id), NULL, &routine, philos + i);
		// usleep(10000);
		i++;
	}
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_param_philo	data;
	t_philo			*philos;

	init_data(&data);
	init_mutex(&data);
	philos = malloc(sizeof(t_philo) * (data.nb_philo + 1));
	if (!philos)
		return (0);
	init_tab_philo(philos, &data);
	if (data.nb_philo == 1)
		routine_solo(philos);
	else
		philo_can_live(&data, philos);
	sleep(1);
	return (0);
}
