/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:33:38 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/06/29 13:33:40 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

static int	check_if_starved(t_philo *philos)
{
	size_t		time_stamp;
	t_timeval	now;
	int			i;

	i = 0;
	while (i < (int)philos->vars->philo_n)
	{
		pthread_mutex_lock(&philos->vars->state_mutex);
		gettimeofday(&now, NULL);
		if (philos->vars->done)
			return (1);
		if (elapsed_time(&philos[i].last_meal, &now) > philos->vars->die_time)
		{
			philos->vars->done = 1;
			time_stamp = elapsed_time(&philos->vars->s_time, &now);
			printf("%zu %zu is dead\n", time_stamp, philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(&philos->vars->state_mutex);
		usleep(50);
		i++;
	}
	return (0);
}

static void	monitor_state(t_philo *philos)
{
	while (1)
	{
		if (check_if_starved(philos))
		{
			pthread_mutex_unlock(&philos->vars->state_mutex);
			break ;
		}
		usleep(500);
	}
}

void	*philo_thread(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].vars->philo_n)
	{
		pthread_create(&(philos[i].thread), NULL, routine, (void *)&philos[i]);
		i++;
	}
	usleep(500);
	monitor_state(philos);
	i = 0;
	while (i < philos[0].vars->philo_n)
	{
		pthread_join(philos[i++].thread, NULL);
	}
	return (NULL);
}
