#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	error(t_data *var)
{
	if (var->philos != NULL)
		free(var->philos);
	if (var->forks != NULL)
		free(var->forks);
	printf("Error\n");
	exit (-1);
}

size_t	elapsed_time(t_data *var)
{
	size_t	sec_diff;
	size_t	usec_diff;

	gettimeofday(&var->end_time, NULL);
	sec_diff = var->end_time.tv_sec - var->start_time.tv_sec;
	usec_diff = var->end_time.tv_usec - var->start_time.tv_usec;

	return ((sec_diff * 1000) + (usec_diff / 1000));
}