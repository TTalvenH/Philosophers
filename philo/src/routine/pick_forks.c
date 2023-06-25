#include "philosophers.h"

static int	starved(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->state_mutex);
	if (philos->vars->done == -2)
	{
		philos->vars->done = philos->id;
		pthread_mutex_unlock(&philos->vars->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philos->vars->state_mutex);
	return (0);
}

int	pick_forks(t_philo *philos)
{
	t_timeval	c_time;

	if (philos->vars->philo_n == 1)
		return (starved(philos));
	if (philos->id & 1)
	{
		pthread_mutex_lock(philos->left);
		state_message(philos, "has taken a fork");
		pthread_mutex_lock(philos->right);
		state_message(philos, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->right);
		state_message(philos, "has taken a fork");
		pthread_mutex_lock(philos->left);
		state_message(philos, "has taken a fork");
	}
	gettimeofday(&c_time, NULL);
	if (elapsed_time(&philos->last_meal, &c_time) > philos->vars->die_time)
		starved(philos);
	return (0);
}
