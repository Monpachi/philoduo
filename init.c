#include "philosophers.h"

int	init_data(t_param_philo *data)
{
	data->nb_philo = 6;
	data->tt_die = 800;
	data->tt_eat = 200;
	data->tt_sleep = 200;
	data->rounds = 0;
	data->fork_state = ft_calloc(data->nb_philo, sizeof(bool));
	if (!data->fork_state)
		return (1);
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (free(data->fork_state), 1);
	return (0);
}

void	destroy_mutex(t_param_philo *data, int compt, int s)
{
	int i;

	i = 0;
	while (i <= compt)
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		if (i == compt && !s)
			break ;
		pthread_mutex_destroy(&data->mutex_state[i]);
		i++;
	}
	free(data->fork_state);
	free(data->mutex_fork);
	free(data->mutex_state);
}

int	init_mutex(t_param_philo *data)
{
	int	i;

	i = 0;
	data->mutex_fork = ft_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	if (!data->mutex_fork)
		return (free(data->fork_state), 1);
	data->mutex_state = ft_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	if (!data->mutex_state)
		return (free(data->fork_state), free(data->mutex_fork), 1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->mutex_fork[i], NULL))
			return (destroy_mutex(data, i, 0), 1);
		if (pthread_mutex_init(&data->mutex_state[i], NULL))
			return (destroy_mutex(data, i, 1), 1);
		i++;
	}
	return (0);
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
		// philos =  da% philo->data->nb_philo
		i++;
	}
	return ;
}
