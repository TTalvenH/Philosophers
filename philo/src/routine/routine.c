#include "philosophers.h"

int	check_starved_or_error(t_philo *philos)
{
	if (pthread_mutex_error(&philos->vars->starved_mutex, LOCK))
		return (-1);
	if (philos->vars->starved)
	{
		if (philos->vars->error)
		{
			thread_error(philos);
			if (pthread_mutex_error(&philos->vars->starved_mutex, UNLOCK))
				return (-1);
			return (-1);
		}
		if (pthread_mutex_error(&philos->vars->starved_mutex, UNLOCK))
			return (-1);
		return (1);
	}
	if (pthread_mutex_error(&philos->vars->starved_mutex, UNLOCK))
		return (-1);
	return (0);
}

int	state_message(t_philo *philos, int task)
{
	size_t		time_stamp;
	t_timeval	c_time;

	gettimeofday(&c_time, NULL);
	time_stamp = elapsed_time(&philos->vars->s_time, &c_time);
	if (task == DEAD)
		return (printf("%zu %zu died\n", time_stamp, philos->id));
	if (!check_starved_or_error(philos))
	{
		if (pthread_mutex_error(&philos->vars->output_mutex, LOCK))
			return (-1);
		if (task == EATING)
			printf("%zu %zu is eating\n", time_stamp, philos->id);
		else if (task == SLEEPING)
			printf("%zu %zu is sleeping\n", time_stamp, philos->id);
		else if (task == THINKING)
			printf("%zu %zu is thinking\n", time_stamp, philos->id);
		else if (task == FORKS)
			printf("%zu %zu has taken a fork\n", time_stamp, philos->id);
		if (pthread_mutex_error(&philos->vars->output_mutex, UNLOCK))
			return (-1);
	}
	return (0);
}

static int	starved(t_philo *philos)
{
	if (pthread_mutex_error(&philos->vars->starved_mutex, LOCK))
		return (-1);
	if (!philos->vars->starved)
	{
		philos->vars->starved = 1;
		state_message(philos, DEAD);
		if (pthread_mutex_error(&philos->vars->starved_mutex, UNLOCK))
			return (-1);
	}
	if (pthread_mutex_error(&philos->vars->starved_mutex, UNLOCK))
		return (-1);
	return (0);
}

static int	eating(t_philo *philos)
{
	state_message(philos, EATING);
	gettimeofday(&philos->last_meal, NULL);
	custom_delay(philos, philos->vars->eat_time);
	if (pthread_mutex_error(&philos->left->lock, LOCK))
		return (-1);
	philos->left->fork = 0;
	if (pthread_mutex_error(&philos->left->lock, UNLOCK))
		return (-1);
	if (pthread_mutex_error(&philos->right->lock, LOCK))
		return (-1);
	philos->right->fork = 0;
	if (pthread_mutex_error(&philos->right->lock, UNLOCK))
		return (-1);
	return (0);
}

static void	sleeping(t_philo *philos)
{
	state_message(philos, SLEEPING);
	custom_delay(philos, philos->vars->sleep_time);
}

void	*routine(void *arg)
{
	t_philo		*philos;
	int			rtn;

	philos = (t_philo *)arg;
	gettimeofday(&philos->last_meal, NULL);
	while (1)
	{
		rtn = check_starved_or_error(philos);
		if (rtn)
			break ;
		if (rtn < 0)
			return ((void *)-1);
		if (pick_forks(philos))
			starved(philos);
		eating(philos);
		sleeping(philos);
		state_message(philos, THINKING);
	}
	return (NULL);
}
