#include "philosophers.h"

void	init_data(t_param_philo *data)
{
	data->nb_of_philo = 5;
	data->time_to_die = 10000;
	data->time_to_eat = 500;
	data->time_to_sleep = 80;
	data->nb_round = 50;
}

void	init_mutex(t_param_philo *data)
{
	int	i;

	i = 0;
	data->mutex_fork = ft_calloc(data->nb_of_philo, sizeof(pthread_mutex_t));
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	return ;
}

void	init_tab_philo(t_philo *tab_philo, t_param_philo *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		tab_philo[i] = (t_philo){0};
		tab_philo[i].param_philo = data;
		tab_philo[i].philo_id = i + 1;
		i++;
	}
	return ;
}
