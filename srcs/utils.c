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

void	print_action(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->data->alive_m);
	if (philo->data->alive == 0)
		printf("%lums	| %d = %s\n",
			diff_time2(philo->data->start_t, now()) / 1000, philo->id, s);
	pthread_mutex_unlock(&philo->data->alive_m);
	pthread_mutex_unlock(&philo->data->mutex_print);
}


void	print_action2(t_philo *philo, char *s)
{
	if (philo->data->alive == 0)
		printf("%lums	| %d = %s\n",
			diff_time2(philo->data->start_t, now()) / 1000, philo->id, s);
}
