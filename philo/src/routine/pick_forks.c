#include "philosophers.h"

static int	get_second(t_fork *first, t_fork *second, t_philo *philos)
{
	while (1)
	{
		if (pthread_mutex_error(&second->lock, LOCK))
			return (-1);
		if (!second->fork)
		{
			second->fork = 1;
			state_message(philos, FORKS);
			if (pthread_mutex_error(&first->lock, UNLOCK))
				return (-1);
			if (pthread_mutex_error(&second->lock, UNLOCK))
				return (-1);
			return (0);
		}
		else
			if (pthread_mutex_error(&second->lock, UNLOCK))
				return (-1);
		custom_delay(philos, 1);
	}
}

static int	get_forks(t_fork *first, t_fork *second, t_philo *philos)
{	

	if (pthread_mutex_error(&first->lock, LOCK))
		return (-1);
	if (!first->fork)
	{
		first->fork = 1;
		state_message(philos, FORKS);
		if (pthread_mutex_error(&first->lock, UNLOCK))
			return (-1);
		return (get_second(first, second, philos));
	}
	else
		if (pthread_mutex_error(&first->lock, UNLOCK))
			return (-1);
	return (1);
}

int	pick_forks(t_philo *philos)
{
	t_timeval	c_time;
	int			rtn;
	while (1)
	{
		gettimeofday(&c_time, NULL);
		if (philos->vars->philo_n == 1)
			return (1);
		if (elapsed_time(&philos->last_meal, &c_time) > philos->vars->die_time)
			return (1);
		if (philos->id & 1)
			rtn = get_forks(philos->left, philos->right, philos);
		else 
			rtn = get_forks(philos->right, philos->left, philos);
		if (rtn < 0)
		{
			philos->vars->error = 1;
			return (-1);
		}
		if (!rtn)
			return (0);
		custom_delay(philos, 1);
	}
}
