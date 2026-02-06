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

void use_forks(t_philo philo, t_program *program)
{
	pthread_mutex_lock(philo.left_fork);
	pthread_mutex_lock(philo.right_fork);
	philo_print(FORK, philo.id, program, get_current_time());
	philo_print(FORK, philo.id, program, get_current_time());
}

void free_forks(t_philo philo)
{
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	eat(t_params params, t_philo *philo, t_control *has_eaten,
	t_program *program)
{
	pthread_mutex_lock(&program->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&program->meal_lock);
	philo_print(EAT, philo->id, program, philo->last_meal);
	ft_usleep(params.time_to_eat);
	philo->times_eaten++;
	pthread_mutex_lock(&has_eaten->mutex);
	has_eaten->stop = true;
	pthread_mutex_unlock(&has_eaten->mutex);
}

void	p_sleep(int time_to_sleep, t_philo philo, t_program *program)
{
	philo_print(SLEEP, philo.id, program, get_current_time());
	ft_usleep(time_to_sleep);
}

void	think(t_params params, t_philo philo, t_program *program)
{
	long	think_time;

	philo_print(THINK, philo.id, program, get_current_time());
	if (params.philo_number % 2 != 0)
	{
		think_time = params.time_to_eat * 2 - params.time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time);
	}
}

void	*philo_functions(void *params_void)
{
	t_params		params;
	t_philo			*philo;
	t_control		*has_eaten;
	t_program		*program;
	t_thread_args	*thread_args;

	thread_args = (typeof(thread_args))params_void;
	params = thread_args->params;
	philo = thread_args->philo;
	has_eaten = thread_args->has_eaten;
	program = thread_args->program;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!program->dead_flag)
	{
		use_forks(*philo, program);
		if (!program->dead_flag)
			eat(params, philo, has_eaten, program);
		free_forks(*philo);
		if (!program->dead_flag)
			p_sleep(params.time_to_sleep, *philo, program);
		if (!program->dead_flag)
			think(params, *philo, program);
	}
	return (NULL);
}
