/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/13 19:53:34 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_input(int argc, char **argv, t_params *params)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		i++;
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (false);
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0)
		return (false);
	if (ft_atoi(argv[4]) <= 0)
		return (false);
	params->philo_number = ft_atoi(argv[1]);
	params->time_to_starve = ft_atoi(argv[2]);
	params->time_to_eat = 1000 * ft_atoi(argv[3]);
	params->time_to_sleep = 1000 * ft_atoi(argv[4]);
	params->max_meals = -1;
	if (argc == 6)
		params->max_meals = ft_atoi(argv[5]);
	return (true);
}

static bool	all_ate_enough(t_program *program, t_params params)
{
	int	i;

	if (params.max_meals == -1)
		return (false);
	i = 0;
	pthread_mutex_lock(&program->meal_lock);
	while (i < params.philo_number)
	{
		if (program->philos[i].times_eaten < params.max_meals)
		{
			pthread_mutex_unlock(&program->meal_lock);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&program->meal_lock);
	return (true);
}

void	main_loop(t_program *program, t_params params)
{
	while (1)
	{
		if (is_dead(program))
			break ;
		if (all_ate_enough(program, params))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = true;
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		usleep(100);
	}
}

static void	cleanup(t_program *p, t_params par, t_thread_args *ta)
{
	join_threads(p->philos, par);
	destroy_mutex(par, p->forks, p);
	free_mallocs(p, p->forks, p->philos);
	free(ta);
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_program		*program;
	t_thread_args	*thread_args;

	if (!parse_input(argc, argv, &params))
		return (1);
	program = init_program(params);
	if (!program)
		return (1);
	init_mutexs(program);
	forks_launchers(params, program);
	thread_args = launchers(params, program);
	if (!thread_args)
	{
		destroy_mutex(params, program->forks, program);
		return (free_program(program), 1);
	}
	set_philos_start(program, params);
	main_loop(program, params);
	cleanup(program, params, thread_args);
	return (0);
}
