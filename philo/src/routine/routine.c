#include "philosophers.h"


void	state_message(t_philo *philos, int task)
{
	size_t		time_stamp;
	t_timeval	c_time;

	gettimeofday(&c_time, NULL);
	time_stamp = elapsed_time(&philos->vars->s_time, &c_time);
	if (!check_starved_state(philos))
	{
		pthread_mutex_lock(&philos->vars->output_mutex);
		if (task == EATING)
			printf("%zu %zu is eating\n", time_stamp, philos->id);
		else if (task == SLEEPING)
			printf("%zu %zu is sleeping\n", time_stamp, philos->id);
		else if (task == THINKING)
			printf("%zu %zu is thinking\n", time_stamp,philos->id);
		else if (task == FORKS)
			printf("%zu %zu has taken a fork\n", time_stamp, philos->id);
		pthread_mutex_unlock(&philos->vars->output_mutex);
	}
	else if (task == DEAD)
		printf("%zu %zu died\n", time_stamp, philos->id);
}

static void	starved(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->starved_mutex);
	if (!philos->vars->starved)
	{
		philos->vars->starved = 1;
		pthread_mutex_unlock(&philos->vars->starved_mutex);
		state_message(philos, DEAD);

	}
	pthread_mutex_unlock(&philos->vars->starved_mutex);
}

static void	eating(t_philo *philos)
{
	state_message(philos, EATING);
	gettimeofday(&philos->last_meal, NULL);
	usleep(philos->vars->eat_time * 1000);
	pthread_mutex_lock(&philos->left->lock);
	philos->left->fork = 0;
	pthread_mutex_unlock(&philos->left->lock);
	pthread_mutex_lock(&philos->right->lock);
	philos->right->fork = 0;
	pthread_mutex_unlock(&philos->right->lock);
}

static void	sleeping(t_philo *philos)
{
	state_message(philos, SLEEPING);
	usleep(philos->vars->sleep_time * 1000);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	gettimeofday(&philos->last_meal, NULL);
	pthread_mutex_unlock(&philos->vars->starved_mutex);
	while (1)
	{
		if (check_starved_state(philos))
			break ;
		if (pick_forks(philos))
			starved(philos);
		eating(philos);
		sleeping(philos);
		state_message(philos, THINKING);
	}
	return (NULL);
}