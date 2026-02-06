/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starving.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/12/13 19:53:34 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_detector(t_params params, t_philo *philo, t_program *program)
{
	long	elapsed_time;

	usleep(50);
	pthread_mutex_lock(&program->meal_lock);
	elapsed_time = get_philo_elapsed_time(*philo);
	pthread_mutex_unlock(&program->meal_lock);
	if (elapsed_time > params.time_to_starve)
	{
		pthread_mutex_lock(&program->dead_lock);
		philo_print(DIE, philo->id, program, get_current_time());
		program->dead_flag = true;
		pthread_mutex_unlock(&program->dead_lock);
	}
}

void	*death_detector_launcher(void *params_void)
{
	t_params		params;
	t_philo			*philo;
	t_program		*program;
	t_thread_args	*thread_args;

	thread_args = (typeof(thread_args))params_void;
	params = thread_args->params;
	philo = thread_args->philo;
	program = thread_args->program;
	while (!program->dead_flag)
	{
		death_detector(params, philo, program);
		usleep(100);
	}
	return (NULL);
}
