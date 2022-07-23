
#include "philosophers.h"

void	lock_state(t_philo *philos, int i)
{
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
}

void	unlock_state(t_philo *philos, int i)
{
	pthread_mutex_unlock(&philos->data->mutex_state[i]);
	if (i == philos->data->nb_philo)
		pthread_mutex_unlock(&philos->data->mutex_state[0]);
	else
		pthread_mutex_unlock(&philos->data->mutex_state[i + 1]);
}

void	change_state(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->data->mutex_state[i]);
	philos->data->fork_state[i] = 0;
	if (i == philos->data->nb_philo)
		philos->data->fork_state[0] = 0;
	else
		philos->data->fork_state[i + 1] = 0;
}

void	lock_fork(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->data->mutex_fork[i]);
	if (i == philos->data->nb_philo)
		pthread_mutex_lock(&philos->data->mutex_fork[0]);
	else
		pthread_mutex_lock(&philos->data->mutex_fork[i + 1]);
}

void	unlock_fork(t_philo *philos, int i)
{
	if (i == philos->data->nb_philo)
		pthread_mutex_unlock(&philos->data->mutex_fork[0]);
	else
		pthread_mutex_unlock(&philos->data->mutex_fork[i + 1]);
	pthread_mutex_unlock(&philos->data->mutex_fork[i]);
}
