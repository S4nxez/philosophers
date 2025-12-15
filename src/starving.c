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

void	interrumpible_sleep(long sleep_ms, t_control *has_eaten, t_philo philo)
{
	long	elapsed_time;

	elapsed_time = get_philo_elapsed_time(philo);
	while (elapsed_time < sleep_ms)
	{
		pthread_mutex_lock(&has_eaten->mutex);
		if (has_eaten->stop)
		{
			pthread_mutex_unlock(&has_eaten->mutex);
			break;
		}
		pthread_mutex_unlock(&has_eaten->mutex);
		usleep(1000);
		elapsed_time = get_philo_elapsed_time(philo);
	}
	has_eaten->stop = false;
}

void	death_detector(t_params params, t_philo *philo, t_program *program)
{
	long	elapsed_time;

	sleep(params.time_to_starve);
	elapsed_time = get_philo_elapsed_time(*philo);
	if (elapsed_time * (-1) > params.time_to_starve * 1000)
	{
		pthread_mutex_lock(&program->dead_lock);
		philo_print(DIE, philo->id, program);
		program->dead_flag = true;
		pthread_mutex_unlock(&program->dead_lock);
	}
}

void *death_detector_launcher(void *params_void)
{
	t_control	*has_eaten;
	t_params	params;
	t_philo		*philo;
	t_program	*program;

	struct
	{
		t_params		params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork;
		pthread_mutex_t	*right_fork;
		t_control		*has_eaten;
		t_program		*program;
	} *args = (typeof(args))params_void;
	params = args->params;
	philo = args->philo;
	has_eaten = args->has_eaten;
	program = args->program;
	while (!program->dead_flag)
	{
		death_detector(params, philo, program);
		interrumpible_sleep(params.time_to_starve, has_eaten, *philo);
	}
	return (NULL);
}