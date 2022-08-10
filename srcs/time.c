#include "philosophers.h"

struct timeval	now(void)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return (time);
}


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
