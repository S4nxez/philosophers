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

void	eat(t_params params, t_philo *philo, t_control *has_eaten,
	t_program *program)
{
	pthread_mutex_lock(&program->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&program->meal_lock);
	philo_print(EAT, philo->id, program, philo->last_meal);
	ft_usleep(params.time_to_eat, program);
	pthread_mutex_lock(&program->meal_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&program->meal_lock);
	pthread_mutex_lock(&has_eaten->mutex);
	has_eaten->stop = true;
	pthread_mutex_unlock(&has_eaten->mutex);
}

void	p_sleep(int time_to_sleep, t_philo philo, t_program *program)
{
	philo_print(SLEEP, philo.id, program, get_current_time());
	ft_usleep(time_to_sleep, program);
}

void	think(t_params params, t_philo philo, t_program *program)
{
	long	think_time;

	philo_print(THINK, philo.id, program, get_current_time());
	if (params.philo_number % 2 != 0)
	{
		think_time = params.time_to_eat * 2 - params.time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time, program);
	}
}

static int	philo_loop(t_thread_args *ta, t_philo *philo, t_program *prg)
{
	if (!use_forks(*philo, prg))
		return (0);
	if (is_dead(prg))
	{
		free_forks(*philo);
		return (0);
	}
	eat(ta->params, philo, ta->has_eaten, prg);
	free_forks(*philo);
	if (is_dead(prg))
		return (0);
	p_sleep(ta->params.time_to_sleep, *philo, prg);
	think(ta->params, *philo, prg);
	return (1);
}

void	*philo_functions(void *params_void)
{
	t_philo			*philo;
	t_program		*program;
	t_thread_args	*thread_args;

	thread_args = (typeof(thread_args))params_void;
	philo = thread_args->philo;
	program = thread_args->program;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!is_dead(program)
		&& philo->times_eaten != thread_args->params.max_meals)
	{
		if (!philo_loop(thread_args, philo, program))
			break ;
	}
	return (NULL);
}
