#include "philosophers.h"

unsigned long	get_time(t_philo *data)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	data->start_t = (unsigned long) time.tv_sec * 1000;
	data->start_t += (unsigned long) time.tv_usec / 1000;
	return (data->start_t);
}

unsigned long	diff_time(t_philo *data)
{
	struct	timeval end_time;

	gettimeofday(&end_time, NULL);
	data->end_t = (unsigned long) end_time.tv_sec * 1000;
	data->end_t += (unsigned long) end_time.tv_usec / 1000;
	return (data->end_t);
}
