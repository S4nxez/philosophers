/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2026/02/06 19:53:34 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_launchers(t_params params, t_program *program)
{
	int	i;

	i = 0;
	while (i < params.philo_number)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		pthread_mutex_init(&program->has_eaten[i].mutex, NULL);
		i++;
	}
	program->start_time = get_current_time();
}

t_thread_args	*launchers(t_params params, t_program *program)
{
	int				i;
	t_thread_args	*thread_args;

	i = 0;
	thread_args = malloc(sizeof(t_thread_args) * params.philo_number);
	if (!thread_args)
		return (NULL);
	while (i < params.philo_number)
	{
		thread_args[i].params = params;
		thread_args[i].philo = &program->philos[i];
		thread_args[i].program = program;
		program->philos[i].left = i;
		if (i + 1 == params.philo_number)
			program->philos[i].right = 0;
		else
			program->philos[i].right = i + 1;
		launch_philo(i, &thread_args[i]);
		i++;
	}
	return (thread_args);
}

void	init_mutexs(t_program *program)
{
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->forks_state_mutex, NULL);
}
