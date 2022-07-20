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

// mutex_lock unlock pour printf
// void	print_action(t_philo *tab_philo, char *s)
// {
// 	static phtread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

// 	pthread_mutex_lock(print_mutex);
// 	printf("%d	| %s\n", tab_philo->philo_id, s);
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
		if (philos->data->fork_state[i] == 0 && philos->data->fork_state[i - 1] == 0)
			return (1);
		else
			return (0);
	}
}

// int	philo_is_hungry(t_philo *philos)
// {
// 	int	time;

// 	if (can_lock(philos))
// 	{
// 		pthread_mutex_lock(&philos->data->mutex_fork[philos->id - 1]);
// 		if (philos->id == philos->data->nb_philo)
// 			pthread_mutex_lock(&philos->data->mutex_fork[0]);
// 		else
// 			pthread_mutex_lock(&philos->data->mutex_fork[philos->id]);
// 		time = diff_time(philos) - philos->start_t;
// 		printf("%dms	| %d = %s has taken a fork 🍴%s\n", time,
// 			philos->id, _YELLOW, _END);
// 		time = diff_time(philos) - philos->start_t;
// 		printf("%dms	| %d is eating\n", time, philos->id);
// 		usleep(philos->data->tt_eat * 1000);
// 		pthread_mutex_unlock(&philos->data->mutex_fork[philos->id - 1]);
// 		if (philos->id == philos->data->nb_philo)
// 			pthread_mutex_unlock(&philos->data->mutex_fork[0]);
// 		else
// 			pthread_mutex_unlock(&philos->data->mutex_fork[philos->id]);
// 	}
// 	else
// 		return (1);
// 	return (0);
// }

int	philo_is_hungry(t_philo *philos)
{
	int	time;
	int	i;

	i = philos->id - 1;
	// Verif si on peut lock les deux fork
	if (!can_lock(philos))
		return (1);

	//On lock l'etat des fork et on met l'etat des fork en busy
	pthread_mutex_lock(&philos->data->mutex_state[i]);
	philos->data->fork_state[i] = 1;
	if (i == philos->data->nb_philo)
	{
		pthread_mutex_lock(&philos->data->mutex_state[0]);
		philos->data->fork_state[0] = 1;
	}
	else
	{
		pthread_mutex_lock(&philos->data->mutex_state[i + 1]);
		philos->data->fork_state[i + 1] = 1;
	}

	time = diff_time(philos) - philos->start_t;
	pthread_mutex_lock(&philos->data->mutex_fork[i]);
	printf("%dms	| %d = %s has taken a fork 🍴%s\n", time,
			philos->id, _YELLOW, _END);

	time = diff_time(philos) - philos->start_t;
	if (i == philos->data->nb_philo)
		pthread_mutex_lock(&philos->data->mutex_fork[0]);
	else
		pthread_mutex_lock(&philos->data->mutex_fork[i + 1]);
	printf("%dms	| %d = %s has taken a fork 🍴%s\n", time,
			philos->id, _YELLOW, _END);
	printf("%dms	| %d is eating\n", time, philos->id);
	usleep(philos->data->tt_eat * 1000);
	if (i == philos->data->nb_philo)
		pthread_mutex_unlock(&philos->data->mutex_fork[0]);
	else
		pthread_mutex_unlock(&philos->data->mutex_fork[i + 1]);
	pthread_mutex_unlock(&philos->data->mutex_fork[i]);
	if (i == philos->data->nb_philo)
	{
		philos->data->fork_state[0] = 0;
		pthread_mutex_unlock(&philos->data->mutex_state[0]);
	}
	else
	{
		philos->data->fork_state[i + 1] = 0;
		pthread_mutex_unlock(&philos->data->mutex_state[i + 1]);
	}
	philos->data->fork_state[i] = 0;
	pthread_mutex_unlock(&philos->data->mutex_state[i]);
	return (0);
}

void	*routine(void *philos_to_cast)
{
	t_philo	*philo;

	philo = (t_philo *) philos_to_cast;
	philo->start_t = get_time(philo);
	//eat
	usleep(10000);
	if (philo_is_hungry(philo))
		printf("%lums	| %d can't eat\n", diff_time(philo) - philo->start_t, philo->id);
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
		usleep(10000);
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
