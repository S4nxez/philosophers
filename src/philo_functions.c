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

void	forks(t_philo philo, pthread_mutex_t *left_fork,
	pthread_mutex_t *right_fork, bool lock, t_program *program)
{
	if (lock)
	{
		pthread_mutex_lock(left_fork);
		philo_print(FORK, philo.id, program);
		pthread_mutex_lock(right_fork);
		philo_print(FORK, philo.id, program);
	}
	else
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
}

void	eat(t_params params, t_philo *philo, t_control *has_eaten,
	t_program *program)
{

	philo->last_meal = philo_print(EAT, philo->id, program);
	sleep(params.time_to_eat);
	philo->times_eaten++;
	pthread_mutex_lock(&has_eaten->mutex);
	has_eaten->stop = true;
	pthread_mutex_unlock(&has_eaten->mutex);
}

void	think(int time_to_think, t_philo philo, t_program *program)
{
	philo_print(THINK, philo.id, program);
	sleep(time_to_think);
}

void	p_sleep(int time_to_sleep, t_philo philo, t_program *program)
{
	philo_print(SLEEP, philo.id, program);
	sleep(time_to_sleep);
}

void	*philo_functions(void *params_void)
{
	t_params	params;
	t_philo		*philo;
	t_control	*has_eaten;
	t_program	*program;

	struct
	{
		t_params		params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork; //TODO meter en el philo
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
		forks(*philo, args->left_fork, args->right_fork, true, program);
		if (!program->dead_flag)
			eat(params, philo, has_eaten, program);
		forks(*philo, args->left_fork, args->right_fork, false, program);
		if (!program->dead_flag)
			think(3, *philo, program); //TODO modificar el tiempo
		if (!program->dead_flag)
			p_sleep(params.time_to_sleep, *philo, program);
	}
	free(args);
	return (NULL);
}
