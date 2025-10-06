/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:18:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/06 20:53:08 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(int time_to_eat, t_philo philo,
	pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork)
{
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	philo_print(3, philo.id, 0);
	sleep(time_to_eat);
	philo_print(3, philo.id, 1);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	think(int time_to_think, t_philo philo)
{
	philo_print(2, philo.id, 0);
	sleep(time_to_think);
	philo_print(2, philo.id, 1);
}

void	p_sleep(int time_to_sleep, t_philo philo)
{
	philo_print(1, philo.id, 0);
	sleep(time_to_sleep);
	philo_print(1, philo.id, 1);
}

void	*philo_functions(void *params_void)
{
	struct {
		t_params		*params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork;
		pthread_mutex_t	*right_fork;
	} *args = (typeof(args))params_void;
	t_params		*params = args->params;
	t_philo			*philo = args->philo;
	pthread_mutex_t	*left_fork = args->left_fork;
	pthread_mutex_t	*right_fork = args->right_fork;

	eat(params->time_to_eat, *philo, left_fork, right_fork);
	think(3, *philo);
	p_sleep(params->time_to_sleep, *philo);
	free(args->philo);
	free(args);
	return (NULL);
}
