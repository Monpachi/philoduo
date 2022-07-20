#include "philosophers.h"

void	init_data(t_param_philo *data)
{
	data->nb_philo = 5;
	data->tt_die = 10000;
	data->tt_eat = 500;
	data->tt_sleep = 80;
	data->rounds = 50;
	data->fork_state = ft_calloc(data->nb_philo, sizeof(bool));
}

void	init_mutex(t_param_philo *data)
{
	int	i;

	i = 0;
	data->mutex_fork = ft_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	return ;
}

void	init_tab_philo(t_philo *philos, t_param_philo *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i] = (t_philo){0};
		philos[i].data = data;
		philos[i].id = i + 1;
		i++;
	}
	return ;
}
