#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	error(t_philo *philos, t_data *var)
{
	free(var->forks);
	free(var);
	free(philos);
	printf("Error\n");
	exit (-1);
}

size_t	elapsed_time(t_timeval *start_time, t_timeval *end_time)
{
	size_t	start_time_msec;
	size_t	end_time_msec;
	start_time_msec =((start_time->tv_sec * 1000)
			+ (start_time->tv_usec / 1000));
	end_time_msec = ((end_time->tv_sec * 1000)
			+ (end_time->tv_usec / 1000));
	return (end_time_msec - start_time_msec);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = '\0';
		s++;
		n--;
	}
}

void	dead_mutex_check(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->starved_mutex);
	pthread_mutex_unlock(&philos->vars->starved_mutex);
}