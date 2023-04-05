#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	pthread_mutex_t *mutex;
	pthread_t 		*threads;
	size_t			philo_n;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
}t_philo;

void	error(t_philo *var);
int		parse_int(char *str, t_philo *var);


#endif