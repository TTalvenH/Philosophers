#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define FORKS 3
# define DEAD 4

typedef struct timeval	t_timeval;

typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	lock;
}t_fork;

typedef struct s_data
{
	size_t			philo_n;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	t_timeval		s_time;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	starved_mutex;
	int				starved;
	t_fork			*forks;
}t_data;

typedef struct s_philo
{	
	pthread_t	thread;
	size_t		id;
	t_timeval	last_meal;
	int			eating;
	int			thinking;
	int			sleeping;
	t_fork		*left;
	t_fork		*right;
	t_data		*vars;
}t_philo;

void	error(t_philo *philos, t_data *var);
int		parse_int(char *str, t_data *var);
void	*philo_thread(t_philo *philos);
void	*routine(void *arg);

size_t	elapsed_time(t_timeval *start_time, t_timeval *end_time);
size_t	start_elapsed_time(t_data *var);
size_t	last_meal_et(size_t last_meal);
void	ft_bzero(void *s, size_t n);

void	state_message(t_philo *philos, int task);
int		pick_forks(t_philo *philos);
int		check_starved_state(t_philo *philos);
void	free_everything(t_philo *philos);



#endif