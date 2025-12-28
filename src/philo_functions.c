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

void	use_forks(t_philo philo, t_program *program)
{
	while (true)
	{
		pthread_mutex_lock(&program->forks_state_mutex);
		if (program->fork_state[philo.right] == FREE
			&& program->fork_state[philo.left] == FREE)
		{
			pthread_mutex_lock(philo.left_fork);
			pthread_mutex_lock(philo.right_fork);
			program->fork_state[philo.right] = TAKEN;
			program->fork_state[philo.left] = TAKEN;
			pthread_mutex_unlock(&program->forks_state_mutex);
			philo_print(FORK, philo.id, program);
			philo_print(FORK, philo.id, program);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&program->forks_state_mutex);
			usleep(500);
		}
	}
}

void	free_forks(t_philo philo, t_program *program)
{
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	pthread_mutex_lock(&program->forks_state_mutex);
	//TODO The thread will wait to free the forks, if another thread is trying
	//to take them it won't free the forks
	program->fork_state[philo.right] = FREE;
	program->fork_state[philo.left] = FREE;
	pthread_mutex_unlock(&program->forks_state_mutex);
}

void	eat(t_params params, t_philo *philo, t_control *has_eaten,
	t_program *program)
{
	philo->last_meal = philo_print(EAT, philo->id, program);
	usleep(params.time_to_eat);
	philo->times_eaten++;
	pthread_mutex_lock(&has_eaten->mutex);
	has_eaten->stop = true;
	pthread_mutex_unlock(&has_eaten->mutex);
}

void	p_sleep(int time_to_sleep, t_philo philo, t_program *program)
{
	philo_print(SLEEP, philo.id, program);
	usleep(time_to_sleep);
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
	while (!program->dead_flag)
	{
		use_forks(*philo, program);
		if (!program->dead_flag)
			eat(params, philo, has_eaten, program);
		free_forks(*philo, program);
		if (!program->dead_flag)
			philo_print(THINK, philo->id, program);
		if (!program->dead_flag)
			p_sleep(params.time_to_sleep, *philo, program);
	}
	return (NULL);
}
