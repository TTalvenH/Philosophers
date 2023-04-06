#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648


typedef struct timeval t_timeval;

typedef struct s_fork
{
	pthread_mutex_t lock;
}t_fork;

typedef struct s_philo
{	
	size_t	id;
	t_fork	*left;
	t_fork	*right;
}t_philo;

typedef struct s_data
{
	size_t			philo_n;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	t_timeval		start_time;
	t_timeval		end_time;
	t_fork			*forks;
	t_philo			*philos;
}t_data;

void	error(t_data *var);
int		parse_int(char *str, t_data *var);
size_t	elapsed_time(t_data *var);



#endif