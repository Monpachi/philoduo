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

void	*routine_solo(t_philo *tab_philo)
{
	t_philo			*blaise_pascal;
	unsigned long	time;


	blaise_pascal = tab_philo;
	blaise_pascal->start_time = get_time(tab_philo);
	usleep(tab_philo->param_philo->time_to_die);
	time = diff_time(tab_philo) - tab_philo->start_time;
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

int	can_lock(t_philo *tab_philo)
{
	if (tab_philo->philo_id == tab_philo->param_philo->nb_of_philo)
	{
		if (tab_philo->fork == 0 && tab_philo[0].fork == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (tab_philo->fork == 0 && tab_philo[tab_philo->philo_id].fork == 0)
			return (1);
		else
			return (0);
	}
}

int	philo_is_hungry(t_philo *tab_philo)
{
	int	time;

	if (can_lock(tab_philo))
	{
		tab_philo->fork = 1;
		tab_philo[tab_philo->philo_id].fork = 1;
		pthread_mutex_lock(&tab_philo->param_philo->mutex_fork[tab_philo->philo_id - 1]);
		if (tab_philo->philo_id == tab_philo->param_philo->nb_of_philo)
			pthread_mutex_lock(&tab_philo->param_philo->mutex_fork[0]);
		else
			pthread_mutex_lock(&tab_philo->param_philo->mutex_fork[tab_philo->philo_id]);
		time = diff_time(tab_philo) - tab_philo->start_time;
		printf("%dms	| %d = %s has taken a fork 🍴%s\n", time,
			tab_philo->philo_id, _YELLOW, _END);
		time = diff_time(tab_philo) - tab_philo->start_time;
		printf("%dms	| %d is eating\n", time, tab_philo->philo_id);
		usleep(tab_philo->param_philo->time_to_eat * 1000);
		pthread_mutex_unlock(&tab_philo->param_philo->mutex_fork[tab_philo->philo_id - 1]);
		if (tab_philo->philo_id == tab_philo->param_philo->nb_of_philo)
			pthread_mutex_unlock(&tab_philo->param_philo->mutex_fork[0]);
		else
			pthread_mutex_unlock(&tab_philo->param_philo->mutex_fork[tab_philo->philo_id]);
tab_philo->fork = 0;
		tab_philo[tab_philo->philo_id].fork = 0;
	}
	else
		return (1);
	return (0);
}

void	*routine(void *tab_philo)
{
	t_philo	*philosophers;

	philosophers = tab_philo;
	philosophers->start_time = get_time(philosophers);
	//eat
	usleep(10000);
	if (philo_is_hungry(philosophers))
		printf("%lums	| %d can't eat\n", diff_time(philosophers) - philosophers->start_time, philosophers->philo_id);
	//sleep
	//think;
	return (NULL);
}


void	philo_can_live(t_param_philo *data, t_philo *tab_philo)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_create(&(tab_philo[i].threads_id), NULL, &routine, tab_philo + i);
		i++;
	}
	while (i < data->nb_of_philo)
	{
		pthread_join(tab_philo[i].threads_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_param_philo	data;
	t_philo			*tab_philo;

	init_data(&data);
	init_mutex(&data);
	tab_philo = malloc(sizeof(t_philo) * (data.nb_of_philo + 1));
	if (!tab_philo)
		return (0);
	init_tab_philo(tab_philo, &data);
	if (data.nb_of_philo == 1)
		routine_solo(tab_philo);
	else
		philo_can_live(&data, tab_philo);
	sleep(1);
	return (0);
}
