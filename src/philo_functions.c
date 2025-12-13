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

void	forks(t_philo philo, pthread_mutex_t	*left_fork,
	pthread_mutex_t	*right_fork, bool lock)
{
	if (lock)
	{
		pthread_mutex_lock(left_fork);
		philo_print(FORK, philo.id);
		pthread_mutex_lock(right_fork);
		philo_print(FORK, philo.id);
	}
	else
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
}

void	eat(t_params params, t_philo *philo)
{
	long	new_meal;
	long	elapsed_time;

	new_meal = philo_print(EAT, philo->id);
	if (philo->last_meal != 0)
		elapsed_time = philo->last_meal - new_meal;
	else
		elapsed_time = philo->born - get_current_time();
	if (elapsed_time * (-1) > params.time_to_starve * 1000)
	{
		philo->dead = true;
		philo_print(DIE, philo->id);
		return ;
	}
	sleep(params.time_to_eat);
	philo->times_eaten++;
	philo->last_meal = new_meal;
}

void	think(int time_to_think, t_philo philo)
{
	philo_print(THINK, philo.id);
	sleep(time_to_think);
}

void	p_sleep(int time_to_sleep, t_philo philo)
{
	philo_print(SLEEP, philo.id);
	sleep(time_to_sleep);
}

void	*philo_functions(void *params_void)
{
	t_params		params;
	t_philo			*philo;

	struct
	{
		t_params		params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork;
		pthread_mutex_t	*right_fork;
	} *args = (typeof(args))params_void;
	params = args->params;
	philo = args->philo;
	while (philo->dead == false)
	{
		forks(*philo, args->left_fork, args->right_fork, true);
		eat(params, philo);
		forks(*philo, args->left_fork, args->right_fork, false);
		think(3, *philo);
		p_sleep(params.time_to_sleep, *philo);
	}
	free(args);
	return (NULL);
}
