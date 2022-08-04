#include "philosophers.h"

// unsigned long	get_time()
// {
// 	struct	timeval time;
// 	unsigned long	start_t;

// 	gettimeofday(&time, NULL);
// 	start_t = (unsigned long) time.tv_sec * 1000;
// 	start_t += (unsigned long) time.tv_usec / 1000;
// 	return (start_t);
// }

struct timeval	now(void)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return (time);
}

// unsigned long	diff_time2(t_param_philo *data)
// {
// 	struct	timeval end_time;
// 	int				time;

// 	gettimeofday(&end_time, NULL);
// 	data->end_t = (unsigned long) end_time.tv_sec * 1000;
// 	data->end_t += (unsigned long) end_time.tv_usec / 1000;
// 	return (data->end_t - data->start_t);
// }

unsigned long	diff_time2(struct timeval start, struct timeval end)
{
	unsigned long		micro_diff;
	unsigned long		sec_diff;

	if (end.tv_usec > start.tv_usec)
	{
		sec_diff = (end.tv_sec - start.tv_sec);
		micro_diff = end.tv_usec - start.tv_usec;
	}
	else
	{
		sec_diff = (end.tv_sec - start.tv_sec) - 1;
		micro_diff = (1000000 - start.tv_usec) + end.tv_usec;
	}
	return ((sec_diff * 1000000) + micro_diff);
}
