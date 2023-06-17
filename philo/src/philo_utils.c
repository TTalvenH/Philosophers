#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>


void	free_everything(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)philos->vars->philo_n)
		pthread_mutex_destroy(&philos->vars->forks[i++].lock);
	free(philos->vars->forks);
	free(philos->vars);
	free(philos);
}

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

int	check_starved_state(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->starved_mutex);
	if (philos->vars->starved)
	{
		pthread_mutex_unlock(&philos->vars->starved_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->vars->starved_mutex);
	return (0);
}