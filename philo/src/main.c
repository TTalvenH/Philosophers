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

int	init_data(t_data *var, char **argv)
{
	size_t i;

	i = 0;
	var->philo_n = parse_int(argv[1], var);
	var->die_time = parse_int(argv[2], var);
	var->eat_time = parse_int(argv[3], var);
	var->sleep_time = parse_int(argv[4], var);
	var->philos = malloc(var->philo_n * sizeof(pthread_t));
	var->forks = malloc(var->philo_n * sizeof(pthread_mutex_t));
	if (!var->philos || !var->forks)
		return (-1);
	while (i < var->philo_n)
	{
		var->philos[i].id = i + 1;
		var->philos[i].left = &var->forks[i];
		var->philos[i].right = &var->forks[(i + 1) % var->philo_n];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	var;

	gettimeofday(&var.start_time, NULL);
	var.philos = NULL;
	var.forks = NULL;
	if (argc == 5)
	{
		if (check_argv (argv) || init_data(&var, argv))
			error(&var);
		while(1)
		{
			usleep(100000);
			printf("%zu\n", elapsed_time(&var));
		}
		return (0);
	}
	printf("Usage: ./philo [n_philo] [time_die] [time_eat] [time_sleep]\n");
}
