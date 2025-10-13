/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:18:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/13 20:00:45 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_params params, t_philo *philo,
	pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork)
{
	long	new_meal;
	long	elapsed_time;

	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	new_meal = philo_print(3, philo->id, 0);
	if (philo->last_meal != 0)
		elapsed_time = philo->last_meal - new_meal;
	if (elapsed_time * (-1) > params.time_to_starve * 1000)
	{
		philo->dead = 1;
		philo_print(4, philo->id, 1);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		return ;
	}
	sleep(params.time_to_eat);
	philo_print(3, philo->id, 1);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	philo->times_eaten++;
	philo->last_meal = new_meal;
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
		t_params		params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork;
		pthread_mutex_t	*right_fork;
	} *args = (typeof(args))params_void;
	t_params		params = args->params;
	t_philo			*philo = args->philo;
	pthread_mutex_t	*left_fork = args->left_fork; //Si hay problema de líneas se podrían poner los tenedores en el t_philo
	pthread_mutex_t	*right_fork = args->right_fork;

	while (philo->dead == 0)
	{
		eat(params, philo, left_fork, right_fork);
		think(3, *philo);
		p_sleep(params.time_to_sleep, *philo);
	}
	free(args);
	return (NULL);
}
