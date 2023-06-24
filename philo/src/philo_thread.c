#include "philosophers.h"
#include <stdio.h>

size_t	elapsed_time(t_timeval *start_time, t_timeval *end_time)
{
	size_t	start_time_msec;
	size_t	end_time_msec;
	start_time_msec =((start_time->tv_sec * 1000)
			+ (start_time->tv_usec / 1000));
	end_time_msec = ((end_time->tv_sec * 1000)
			+ (end_time->tv_usec / 1000));
	return (end_time_msec - start_time_msec);
}

void	custom_delay(t_philo *philo, unsigned int msec)
{
	size_t	time;
	t_timeval current_time;

	gettimeofday(&current_time, NULL);
	time = elapsed_time(&philo->vars->s_time, &current_time);
	time += msec;
	while (time > elapsed_time(&philo->vars->s_time, &current_time))
	{
		usleep(500);
		gettimeofday(&current_time, NULL);
	}
}

void	*philo_thread(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].vars->philo_n)
	{
		pthread_create(&(philos[i].thread), NULL, routine, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < philos[0].vars->philo_n)
		pthread_join(philos[i++].thread, NULL);
	if (philos->vars->error)
		printf("Error\n");
	return (NULL);
}
