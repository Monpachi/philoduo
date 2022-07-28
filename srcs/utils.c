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
	printf("%lums	| %d = %s\n", diff_time2(philo->data), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_print);
}
