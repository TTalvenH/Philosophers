#include "philosophers.h"

static int	starved(t_philo *philos)
{
	size_t		time_stamp;
	t_timeval	c_time;

	pthread_mutex_lock(&philos->vars->state_mutex);
	if (!philos->vars->done)
	{
		philos->vars->done = 1;
		gettimeofday(&c_time, NULL);
		time_stamp = elapsed_time(&philos->vars->s_time, &c_time);
		printf("%zu %zu is dead\n", time_stamp, philos->id);
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
		return (1);
	if (philos->id & 1)
	{
		pthread_mutex_lock(philos->left);
		pthread_mutex_lock(philos->right);
	}
	else
	{
		pthread_mutex_lock(philos->right);
		pthread_mutex_lock(philos->left);
	}
	gettimeofday(&c_time, NULL);
	if (elapsed_time(&philos->last_meal, &c_time) > philos->vars->die_time)
		starved(philos);
	return (0);
}
