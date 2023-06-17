#include "philosophers.h"

static int	get_forks(t_philo *philos)
{	
	pthread_mutex_lock(&philos->left->lock);
	if (!philos->left->fork)
	{
		pthread_mutex_lock(&philos->right->lock);
		if (!philos->right->fork)
		{
			philos->left->fork = 1;
			philos->right->fork = 1;
			state_message(philos, FORKS);
			state_message(philos, FORKS);
			pthread_mutex_unlock(&philos->left->lock);
			pthread_mutex_unlock(&philos->right->lock);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&philos->left->lock);
			pthread_mutex_unlock(&philos->right->lock);
		}
	}
	else
		pthread_mutex_unlock(&philos->left->lock);
	return (1);
}

int	pick_forks(t_philo *philos)
{
	t_timeval	c_time;

	while (1)
	{
		gettimeofday(&c_time, NULL);
		if (philos->vars->philo_n == 1)
			return (1);
		if (elapsed_time(&philos->last_meal, &c_time) > philos->vars->die_time)
			return (1);
		dead_mutex_check(philos);
		if (!get_forks(philos))
			return (0);
		usleep(50);
	}
}
