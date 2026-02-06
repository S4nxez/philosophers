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
	philo->born = prg->start_time;
	philo->left_fork = &prg->forks[i];
	if (i + 1 == thread_args->params.philo_number)
		philo->right_fork = &prg->forks[0];
	else
		philo->right_fork = &prg->forks[i + 1];
	prg->has_eaten[i].stop = false;
	thread_args->has_eaten = &prg->has_eaten[i];
	pthread_create(&philo->thread, NULL, philo_functions,
		(void *)thread_args);
	pthread_create(&philo->death_thread, NULL,
		death_detector_launcher, (void *)thread_args);
}

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
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag)
		{
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&program->dead_lock);
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

int	main(int argc, char **argv)
{
	t_params		params;
	t_program		*program;
	t_thread_args	*thread_args;

	if (!parse_input(argc, argv, &params))
		return (1);
	program = malloc(sizeof(t_program));
	program->philos = malloc(sizeof(t_philo) * params.philo_number);
	program->forks = malloc(sizeof(pthread_mutex_t) * params.philo_number);
	program->has_eaten = malloc(sizeof(t_control) * params.philo_number);
	program->dead_flag = false;
	init_mutexs(program);
	forks_launchers(params, program);
	thread_args = launchers(params, program);
	main_loop(program, params);
	join_threads(program->philos, params);
	destroy_mutex(params, program->forks, program->has_eaten, program);
	free_mallocs(program, program->forks, program->has_eaten,
		program->philos);
	free(thread_args);
	return (0);
}
