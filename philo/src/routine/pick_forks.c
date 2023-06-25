#include "philosophers.h"

int	pick_forks(t_philo *philos)
{
	if (philos->id & 1)
	{
		pthread_mutex_lock(philos->left);
		state_message(philos, "has taken a fork");
		if (philos->vars->philo_n == 1)
			return (usleep(philos->vars->die_time * 1000 + 1000));
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
	return (0);
}
