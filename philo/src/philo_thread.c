#include "philosophers.h"
#include <stdio.h> //! do we need?

void	start_philos(t_philo *philos)
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
	{
		if (pthread_join(philos[i].thread, NULL))
			printf("join fail\n");
		i++;
	}
}

void	*philo_thread(t_philo *philos)
{
	start_philos(philos);
	return (NULL);
}	
