#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"
#include <unistd.h>

static int	check_argv(char **argv)
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

static t_philo	*init_philos(t_data *var)
{
	t_philo *philos;
	size_t	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * var->philo_n);
	if (!philos)
		error(NULL, var);
	ft_bzero((void *)philos, sizeof(t_philo) * var->philo_n);
	while (i < var->philo_n)
	{
		philos[i].id = i + 1; 	
		philos[i].left = &var->forks[i];
		philos[i].right = &var->forks[(i + 1) % var->philo_n];
		philos[i].vars = var;
		i++;
	}
	return (philos);
}

static int	init_var_mutex(t_data *var)
{
	int	i;

	i = 0;
	while (i < (int)var->philo_n)
	{
		if (pthread_mutex_init(&var->forks[i++].lock, NULL))
			return (-1);
	}
	if (pthread_mutex_init(&var->output_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&var->starved_mutex, NULL))
		return (-1);
	return (0);
}

static t_data	*init_var(char **argv)
{
	t_data *var;

	var = malloc(sizeof(t_data));
	if (!var)
		error(NULL, NULL);
	ft_bzero((void *)var, sizeof(t_data));
	gettimeofday(&var->s_time, NULL);
	var->philo_n = parse_int(argv[1], var);
	var->die_time = parse_int(argv[2], var);
	var->eat_time = parse_int(argv[3], var);
	var->sleep_time = parse_int(argv[4], var);
	var->forks = malloc(var->philo_n * sizeof(t_fork));
	if (!var->forks || !var->philo_n)
		error(NULL, var);
	ft_bzero((void *)var->forks, sizeof(var->philo_n * sizeof(t_fork)));
	if (init_var_mutex(var))
		error(NULL, var);
	return (var);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	*var;

	philos = NULL;
	var = NULL;
	if (argc == 5)
	{
		check_argv(argv);
		var = init_var(argv);
		philos = init_philos(var);
		philo_thread(philos);
		return (0);
	}
	printf("Usage: ./philo [n_philo] [time_die] [time_eat] [time_sleep]\n");
}
