#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void	error(t_philo *var)
{
	if (var->threads != NULL)
		free(var->threads);
	if (var->mutex != NULL)
		free(var->mutex);
	printf("Error\n");
	exit (-1);
}
