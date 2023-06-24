#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	free_everything(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)philos->vars->philo_n)
		pthread_mutex_destroy(&philos->vars->forks[i++]);
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

int	state_message(t_philo *philos, char *message)
{
	size_t		time_stamp;
	t_timeval	c_time;

	pthread_mutex_lock(&philos->vars->output_mutex);
	if (!check_state(philos) && !philos->i)
	{
		gettimeofday(&c_time, NULL);
		time_stamp = elapsed_time(&philos->vars->s_time, &c_time);
		printf("%zu %zu %s\n", time_stamp, philos->id, message);
	}
	pthread_mutex_unlock(&philos->vars->output_mutex);
	return (0);
}

int	check_state(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->state_mutex);
	if (philos->vars->philos_done_eating == philos->vars->philo_n)
		philos->vars->done = 1;
	if (philos->vars->done)
	{
		pthread_mutex_unlock(&philos->vars->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->vars->state_mutex);
	return (0);
}
