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

int	init_data(t_philo **philos, char **argv)
{
	t_data	*var;
	size_t	i;

	i = 0;

	var = malloc(sizeof(t_data));

	var->forks = NULL;
	gettimeofday(&var->start_time, NULL);
	var->philo_n = parse_int(argv[1], philos);
	var->die_time = parse_int(argv[2], philos);
	var->eat_time = parse_int(argv[3], philos);
	var->sleep_time = parse_int(argv[4], philos);
	var->start_time_msec = 0;
	var->forks = malloc(var->philo_n * sizeof(t_fork));
	philos = malloc(var->philo_n * sizeof(t_philo *));
	if (!philos || !var->forks)
		return (-1);
	while (i < var->philo_n)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->thread = NULL;
		philos[i]->id = i + 1;
		philos[i]->left = &var->forks[i];
		philos[i]->right = &var->forks[(i + 1) % var->philo_n];
		philos[i]->vars = var;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	**philos;

	philos = NULL;
	if (argc == 5)
	{
		if (check_argv (argv) || init_data(philos, argv))
			error(philos);
		printf("%zu\n", philos[0]->vars->philo_n);
		exit(0);
		philo_thread(philos);
		return (0);
	}
	printf("Usage: ./philo [n_philo] [time_die] [time_eat] [time_sleep]\n");
}
