#include "philosophers.h"

static int	get_forks_first_left(t_philo *philos)
{	
	pthread_mutex_lock(&philos->left->lock);
	if (!philos->left->fork)
	{
		philos->left->fork = 1;
		state_message(philos, FORKS);
		pthread_mutex_unlock(&philos->left->lock);
		while (1)
		{
			pthread_mutex_lock(&philos->right->lock);
			if (!philos->right->fork)
			{
				philos->right->fork = 1;
				state_message(philos, FORKS);
				pthread_mutex_unlock(&philos->left->lock);
				pthread_mutex_unlock(&philos->right->lock);
				return (0);
			}
			else
				pthread_mutex_unlock(&philos->right->lock);
		}
	}
	else
		pthread_mutex_unlock(&philos->left->lock);
	return (1);
}

static int	get_forks_first_right(t_philo *philos)
{	
	pthread_mutex_lock(&philos->right->lock);
	if (!philos->right->fork)
	{
		philos->right->fork = 1;
		state_message(philos, FORKS);
		pthread_mutex_unlock(&philos->right->lock);
		while (1)
		{
			pthread_mutex_lock(&philos->left->lock);
			if (!philos->left->fork)
			{
				philos->left->fork = 1;
				state_message(philos, FORKS);
				pthread_mutex_unlock(&philos->right->lock);
				pthread_mutex_unlock(&philos->left->lock);
				return (0);
			}
			else
				pthread_mutex_unlock(&philos->left->lock);
		}
	}
	else
		pthread_mutex_unlock(&philos->right->lock);
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
		if (philos->id & 1)
		{
			if (!get_forks_first_left(philos))
				return (0);
		}
		else 
		{
			if (!get_forks_first_right(philos))
				return (0);
		}
	}
}
