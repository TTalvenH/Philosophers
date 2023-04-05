#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"



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

int	init_philo(t_philo *var, char **argv)
{
	var->philo_n = parse_int(argv[1], var);
	var->die_time = parse_int(argv[2], var);
	var->eat_time = parse_int(argv[3], var);
	var->sleep_time = parse_int(argv[4], var);
	var->threads = malloc(var->philo_n * sizeof(pthread_t));
	var->mutex = malloc(var->philo_n * sizeof(pthread_mutex_t));
	if (!var->threads || !var->mutex)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	var;

	var.threads = NULL;
	var.mutex = NULL;
	if (argc == 5)
	{
		if (check_argv (argv) || init_philo(&var, argv))
			error(&var);
		printf("%zu\n", var.philo_n);
		printf("%zu\n", var.die_time);
		printf("%zu\n", var.eat_time);
		printf("%zu\n", var.sleep_time);

		return (0);
	}
	printf("Usage: ./philo [n_philo] [time_die] [time_eat] [time_sleep]\n");
}
