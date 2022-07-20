#include "philosophers.h"

unsigned long	get_time(t_philo *data)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	data->start_time = (long) time.tv_sec * 1000;
	return (data->start_time);
}

unsigned long	diff_time(t_philo *data)
{
	struct	timeval end_time;

	gettimeofday(&end_time, NULL);
	data->end_time = (long long) end_time.tv_sec * 1000;
	return (data->end_time);
}
