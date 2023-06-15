#include "philosophers.h"
#include <stdio.h> //! do we need?

// void	pick_forks(t_data *var)
// {

// }

void	*routine(void *arg)
{
	t_philo	*philos;
	int		eating;
	int		thinking;
	int		sleeping;

	eating = 0;
	thinking = 0;
	sleeping = 0;
	philos = (t_philo *)arg;
	// while (1)
	// {
	// 	pick_forks(var);
	// 	if (eating)
	// 	{

	// 	}
	// 	else if (thinking)
	// 	{

	// 	}
	// 	else if (sleeping)
	// 	{

	// 	}
	// }
	printf("test\n");
	return (NULL);
}

void	start_philos(t_philo **philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0]->vars->philo_n)
	{
		pthread_create(&philos[i]->thread, NULL, routine, (void *)philos[i]);
		i++;
	}
}

void	*philo_thread(t_philo **philos)
{
	start_philos(philos);
	return (NULL);
}	
