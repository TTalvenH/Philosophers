#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LOCK 0
# define UNLOCK 1

typedef struct timeval	t_timeval;

typedef struct s_data
{
	size_t			philo_n;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			must_eat;
	size_t			philos_done_eating;
	t_timeval		s_time;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	eaten_mutex;
	pthread_mutex_t	*forks;
	int				done;
}t_data;

typedef struct s_philo
{	
	pthread_t			thread;
	size_t				id;
	t_timeval			last_meal;
	int					eating;
	int					thinking;
	int					sleeping;
	int					i;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_data				*vars;
}t_philo;

int		parse_int(char *str, t_data *var);
void	*philo_create(t_philo *philos);
void	*routine(void *arg);

size_t	elapsed_time(t_timeval *start_time, t_timeval *end_time);
size_t	start_elapsed_time(t_data *var);

int		state_message(t_philo *philos, char *message);
int		pick_forks(t_philo *philos);
int		check_state(t_philo *philos);
void	custom_delay(t_philo *philo, unsigned int msec);

//philo_utils
void	error(t_philo *philos, t_data *var);
void	free_everything(t_philo *philos);
int		check_state(t_philo *philos);
int		state_message(t_philo *philos, char *message);


#endif