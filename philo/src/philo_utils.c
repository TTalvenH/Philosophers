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

void	thread_error(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)philos->vars->philo_n)
		pthread_mutex_destroy(&philos->vars->forks[i++].lock);
}

int	pthread_mutex_error(pthread_mutex_t *mutex, int	lock)
{
	if (lock == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (-1);
	}
	else if (lock == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (-1);
	}
	return (0);
}