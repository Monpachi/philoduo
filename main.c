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

// void	*routine_solo(t_philo *philos)
// {
// 	t_philo			*blaise_pascal;
// 	unsigned long	time;


// 	blaise_pascal = philos;
// 	blaise_pascal->start_t = get_time(philos);
// 	usleep(philos->data->tt_die);
// 	time = diff_time(philos) - philos->start_t;
// 	printf("%ld ms	| \033[0;31mphilo 1 died 💀 \n\033[0m", time);
// 	return (NULL);
// }

// void	print_action(t_philo *philos, char *s)
// {
// 	int	time;

// 	time = diff_time(philos) - philos->start_t;
// 	pthread_mutex_lock(philos->data->mutex_print);
// 	printf("%d	| %d %s\n", time, philos->id, s);
// 	pthread_mutex_unlock(philos->data->mutex_print);
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

int	philo_is_hungry(t_philo *philos)
{
	int	time;
	int	i;

	i = philos->id - 1;
	lock_state(philos, i);
	unlock_state(philos, i);
	time = diff_time(philos->data) - philos->data->start_t;
	lock_forks(philos, i);
	// print_action(philos, FORK_MSG);
	// print_action(philos, FORK_MSG);
	// print_action(philos, EAT_MSG);
	printf("%dms	| %d = %s\n", time, philos->id, FORK_MSG);
	printf("%dms	| %d = %s\n", time, philos->id, FORK_MSG);
	printf("%dms	| %d = %s\n", time, philos->id, EAT_MSG);
	philos->last_meal = diff_time(philos->data);
	change_state(philos, i);
	usleep(philos->data->tt_eat * 1000);
	unlock_forks(philos, i);
	return (0);
}




bool	asleep_think(t_philo *philos)
{
	int	time;

	time = diff_time(philos->data) - philos->data->start_t;
	printf("%dms	| %d = %s\n", time, philos->id, SLEEP_MSG);
	usleep(philos->data->tt_sleep);
	time = diff_time(philos->data) - philos->data->start_t;
	printf("%dms	| %d = %s\n", time, philos->id, THINKING_MSG);
	return (0);
}

// void	ft_manager(t_philo *philo)
// {
// 	t_param_philo	*data;
// 	int				status;
// 	int				i;

// 	status = 1;
// 	data = philo->data;
// 	while (status)
// 	{
// 		i = -1;
// 		while (status && ++i < data->nb_philo)
// 		{
// 			status = ft_deathcheck(philo, data, get_time(data->start_t));
// 			if (!status)
// 				return ;
// 			// pthread_mutex_lock(&data->eat_m);
// 			// if (data-> == data->nb_philo)
// 			// {
// 			// 	ft_stop(data);
// 			// 	status = 0;
// 			// }
// 			// pthread_mutex_unlock(&data->eat_m);
// 		}
// 		if (status)
// 			usleep(250);
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


void	*routine(void *philos_to_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philos_to_cast;
	if (philo->id % 2)
		usleep(philo->data->tt_eat / 2);
	while (1)//not dead
	{
		philo_is_hungry(philo);
		asleep_think(philo);
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
