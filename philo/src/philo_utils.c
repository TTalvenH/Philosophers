#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	error(t_philo **philos)
{
	philos = NULL;
	printf("Error\n");
	exit (-1);
}

size_t	elapsed_time(t_data *var)
{
	size_t	end_time_msec;

	if (!var->start_time_msec)
		var->start_time_msec = ((var->start_time.tv_sec * 1000) \
		+ (var->start_time.tv_usec / 1000));
	gettimeofday(&var->end_time, NULL);
	end_time_msec = ((var->end_time.tv_sec * 1000)
			+ (var->end_time.tv_usec / 1000));
	return (end_time_msec - var->start_time_msec);
}