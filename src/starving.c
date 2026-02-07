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

void	set_philos_start(t_program *prg, t_params params)
{
	int	i;

	pthread_mutex_lock(&prg->dead_lock);
	prg->start_time = get_current_time();
	i = 0;
	while (i < params.philo_number)
	{
		prg->philos[i].born = prg->start_time;
		prg->philos[i].last_meal = prg->start_time;
		i++;
	}
	prg->ready = 1;
	pthread_mutex_unlock(&prg->dead_lock);
}

void	launch_philo(int i, t_thread_args *thread_args)
{
	t_philo		*philo;
	t_program	*prg;

	philo = thread_args->philo;
	prg = thread_args->program;
	philo->id = i + 1;
	philo->times_eaten = 0;
	philo->dead = 0;
	philo->last_meal = 0;
	philo->born = 0;
	philo->left_fork = &prg->forks[i];
	if (i + 1 == thread_args->params.philo_number)
		philo->right_fork = &prg->forks[0];
	else
		philo->right_fork = &prg->forks[i + 1];
	pthread_create(&philo->thread, NULL, philo_functions,
		(void *)thread_args);
	pthread_create(&philo->death_thread, NULL,
		death_detector_launcher, (void *)thread_args);
}

void	death_detector(t_params params, t_philo *philo, t_program *program)
{
	long	elapsed_time;

	usleep(50);
	pthread_mutex_lock(&program->meal_lock);
	elapsed_time = get_philo_elapsed_time(*philo);
	pthread_mutex_unlock(&program->meal_lock);
	if (elapsed_time > params.time_to_starve)
		philo_print(DIE, philo->id, program, get_current_time());
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
	wait_ready(program);
	while (!is_dead(program))
	{
		death_detector(params, philo, program);
		usleep(100);
	}
	return (NULL);
}
