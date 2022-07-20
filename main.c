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

void	philo_is_hungry(t_philo *tab_philo)
{
	int	time;

	time = diff_time(tab_philo) - tab_philo->start_time;
	printf("%d | %d has taken a fork 🍴\n\033[0m\n", time,
		tab_philo->philo_id);
}

void	*routine(void *tab_philo)
{
	t_philo	*philosophers;

	// usleep(1000000);
	philosophers = tab_philo;
	philosophers->start_time = get_time(philosophers);
	printf("id %d | %ld = \033[0;33mphilosophers->start_time033\n", philosophers->philo_id,
		philosophers->start_time);
	//eat
	// philo_is_hungry(tab_philo);
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
		usleep(1000000);
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

	/*Ici, j'ai du faire le malloc dans le main pour que ca fonctionne
		Si je faisais dans la fonction, les donnees ne s'echangeait pas,
		et ca faisais un segfault.
		En faisant ca ici, j'ai pas eu le soucis, et du coup, ca devait surement
		etre sur la stack
	*/
	tab_philo = malloc(sizeof(t_philo) * (data.nb_of_philo + 1));
	if (!tab_philo)
		return (0);
	init_tab_philo(tab_philo, &data);

	/*j'ai passe le nombre de param.philo.nb_philo a 2 pour verifier, que
		j'avais bien un tableau de 2, avec le philo id accessible de partout, et
		bien a 2 aussi du coup
		J'ai aussi verifier que toute les donnees etaient bien init*/
	// printf("nombre id = %d\n", tab_philo[0].philo_id);
	// printf("nombre id = %d\n", tab_philo[1].philo_id);

	/*Si tu veux tester le programme avec 1 philo, change le nb_philo dans les
	 param, ca fonctionne niquel */
	if (data.nb_of_philo == 1)
		routine_solo(tab_philo);
	else
		philo_can_live(&data, tab_philo);
	return (0);
}
