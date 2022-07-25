#include "philosophers.h"


// int	ft_deathcheck(t_philo *philos, t_param_philo *data, unsigned long time)
// {
// 	pthread_mutex_lock(philos->last_meal_m);
// 	if (time_diff(philos->last_meal, time) >= data->tt_die)
// 	{
// 		printf("%dms	| %d = %s\n", time, philos->id, DEAD_MSG);
// 		ft_stop(data);
// 		pthread_mutex_unlock(philos->last_meal_m);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(philos->last_meal_m);
// 	return (1);
// }

// void	ft_sleep(int time, t_param_philo *data)
// {
// 	struct timeval	debut;

// 	gettimeofday(&debut, NULL);
// 	while (get_time(&debut) < time && !ft_checkdead(data))
// 	{
// 		usleep(200);
// 	}
// }

// void	*routine(void *philos_to_cast)
// {
// 	t_philo	*philo;
// 	int		stop;

// 	philo = (t_philo *) philos_to_cast;
// 	if (!(philo->id % 2))
// 		usleep(philo->data->tt_eat / 2);
// 	while (1)
// 	{
// 		if (philo_is_hungry(philo) || asleep_think(philo))
// 		{
// 			printf("%lums	| %d SHIT\n", diff_time(philo->data) - philo->data->start_t, philo->id);
// 			stop = 1;
// 			return (NULL);
// 		}
// 		philo->count_r++;
// 	}
// 	printf("philo->count = %d\n", philo->count_r);
// 	return (NULL);
// }

// int	ft_deathcheck(t_philo *philos, t_param_philo *data, unsigned long time)
// {
// 	int	i;

// 	i = 0;
// 	while (philos->data->nb_philo > i)
// 	{
// 		if (diff_time())
// 		i++;

// 	}

// 	// pthread_mutex_lock(philos->last_meal_m);
// 	if (time_diff(philos->last_meal, time) >= data->tt_die)
// 	{
// 		printf("%dms	| %d = %s\n", time, philos->id, DEAD_MSG);
// 		ft_stop(data);
// 		pthread_mutex_unlock(philos->last_meal_m);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(philos->last_meal_m);
// 	return (1);
// }

int	philo_is_hungry(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->mutex_fork[(philo->id + 1) % philo->data->nb_philo]);
		// printf("%d locked %d\n",philo->id, (philo->id + 1) % philo->data->nb_philo);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_fork[((philo->id) - 1 ) % philo->data->nb_philo]);
		// printf("%d locked %d\n",philo->id, (philo->id));
	}
	printf("%lums	| %d = %s\n", diff_time2(philo->data), philo->id, FORK_MSG);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->mutex_fork[((philo->id) - 1 )% philo->data->nb_philo]);
		// printf("%d locked %d\n",philo->id, (philo->id));
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_fork[(philo->id + 1) % philo->data->nb_philo]);
		// printf("%d locked %d\n",philo->id, (philo->id + 1) % philo->data->nb_philo);
	}
	printf("%lums	| %d = %s\n", diff_time2(philo->data), philo->id, FORK_MSG);
	printf("%lums	| %d = %s\n", diff_time2(philo->data), philo->id, EAT_MSG);
	philo->last_meal = diff_time(philo->data);
	usleep(1000 * philo->data->tt_eat);

	pthread_mutex_unlock(&philo->data->mutex_fork[(philo->id) - 1]);
	// printf("%d unlocked %d\n",philo->id, (philo->id));
	pthread_mutex_unlock(&philo->data->mutex_fork[(philo->id + 1) % philo->data->nb_philo]);
	// printf("%d unlocked %d\n",philo->id, (philo->id + 1) % philo->data->nb_philo);
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

	printf("%lums	| %d = %s\n", diff_time2(philos->data), philos->id, SLEEP_MSG);
	usleep(philos->data->tt_sleep);
	printf("%lums	| %d = %s\n", diff_time2(philos->data), philos->id, THINKING_MSG);
	return (0);
}

void	*routine(void *philos_to_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philos_to_cast;
	if (philo->id % 2)
		usleep(philo->data->tt_eat / 2);
	while (1)//not dead
	{
		philo_is_hungry(philo);
		// asleep_think(philo);
	}

}

void	philo_dead(t_param_philo *data, t_philo *philos, int compt)
{
	int	i;

	i = 0;
	while (i <= compt)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

int	philo_can_live(t_param_philo *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_t = get_time(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&(philos[i].thread_id), NULL, &routine, philos + i))
			return (philo_dead(data, philos, i), 1);
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
	philo_can_live(&data, philos);
	sleep(1);
	return (0);
}
