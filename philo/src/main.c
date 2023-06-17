#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"
#include <unistd.h>

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < 5)
	{
		j = 0;
		if (argv[i][j] == '-' || (argv[i][j] == '+' && !argv[i][++j]))
			return (-1);
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_philo *philos, t_data *var)
{
	size_t	i;

	i = 0;
	ft_bzero((void *)philos, sizeof(t_philo));
	while (i < var->philo_n)
	{
		philos[i].thread = (pthread_t)malloc(sizeof(pthread_t));
		if (!philos[i].thread)
			return (-1);
		philos[i].id = i + 1; 	
		philos[i].left = &var->forks[i];
		philos[i].right = &var->forks[(i + 1) % var->philo_n];
		philos[i].vars = var;
		i++;
	}
	return (0);
}

int	init_var(t_data *var, char **argv)
{
	int	i;

	i = 0;
	gettimeofday(&var->s_time, NULL);
	var->philo_n = parse_int(argv[1], var);
	var->die_time = parse_int(argv[2], var);
	var->eat_time = parse_int(argv[3], var);
	var->sleep_time = parse_int(argv[4], var);
	var->forks = malloc(var->philo_n * sizeof(t_fork));
	ft_bzero((void *)var->forks, sizeof(var->philo_n * sizeof(t_fork)));
	if (!var->forks)
		return (-1);
	while (i < (int)var->philo_n)
		pthread_mutex_init(&var->forks[i++].lock, NULL);
	pthread_mutex_init(&var->output_mutex, NULL);
	pthread_mutex_init(&var->starved_mutex, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	*var;

	if (argc == 5)
	{
		var = malloc(sizeof(t_data));
		if (check_argv (argv) || init_var(var, argv))
			error(var);
		philos = malloc(sizeof(t_philo) * var->philo_n);
		if (!philos || init_philos(philos, var) < 0)
			error(var);
		philo_thread(philos);
		return (0);
	}
	
	printf("Usage: ./philo [n_philo] [time_die] [time_eat] [time_sleep]\n");
}
