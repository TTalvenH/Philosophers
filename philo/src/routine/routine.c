/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:52:08 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/06/28 15:52:14 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	modify_eaten_state(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->eaten_mutex);
	philos->vars->philos_done_eating++;
	philos->i = 1;
	pthread_mutex_lock(&philos->vars->state_mutex);
	if (philos->vars->philos_done_eating == philos->vars->philo_n)
		philos->vars->done = 1;
	pthread_mutex_unlock(&philos->vars->state_mutex);
	pthread_mutex_unlock(&philos->vars->eaten_mutex);
}

static void	eating(t_philo *philos, size_t *eaten)
{
	state_message(philos, "is eating");
	pthread_mutex_lock(&philos->vars->state_mutex);
	gettimeofday(&philos->last_meal, NULL);
	pthread_mutex_unlock(&philos->vars->state_mutex);
	custom_delay(philos, philos->vars->eat_time);
	pthread_mutex_unlock(philos->left);
	pthread_mutex_unlock(philos->right);
	if (philos->vars->must_eat
		&& !philos->i && ++*eaten == philos->vars->must_eat)
		modify_eaten_state(philos);
}

void	*routine(void *arg)
{
	t_philo		*philos;
	size_t		eaten;

	eaten = 0;
	philos = (t_philo *)arg;
	gettimeofday(&philos->last_meal, NULL);
	if (parity((int)philos->id))
		usleep(500);
	while (1)
	{
		if (check_state(philos))
		{
			break ;
		}
		if (parity(philos->vars->philo_n))
			custom_delay(philos, philos->vars->eat_time - 10);
		pick_forks(philos);
		eating(philos, &eaten);
		state_message(philos, "is sleeping");
		custom_delay(philos, philos->vars->sleep_time);
		state_message(philos, "is thinking");
	}
	return (NULL);
}
