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

void	launch_philo(t_params params, int i, t_philo *philo,
	pthread_mutex_t *forks, t_control *has_eaten,
	t_thread_args *thread_args)
{
	philo->id = i + 1;
	philo->times_eaten = 0;
	philo->dead = 0;
	philo->last_meal = 0;
	philo->born = thread_args->program->start_time;
	philo->left_fork = &forks[i];
	if (i + 1 == params.philo_number)
		philo->right_fork = &forks[0];
	else
		philo->right_fork = &forks[i + 1];
	has_eaten[i].stop = false;
	thread_args->has_eaten = &has_eaten[i];
	pthread_create(&philo->thread, NULL, philo_functions, (void *)thread_args);
	pthread_create(&philo->death_thread, NULL, death_detector_launcher,
		(void *)thread_args);
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
	if (ft_atoi(argv[1]) > 200)
		return (false);
	params->philo_number = ft_atoi(argv[1]);
	params->time_to_starve =  ft_atoi(argv[2]);
	params->time_to_eat = 1000 * ft_atoi(argv[3]);
	params->time_to_sleep = 1000 * ft_atoi(argv[4]);
	if (argc == 6)
		params->max_meals = ft_atoi(argv[5]);
	return (true);
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;
	t_control		*has_eaten;
	t_program		*program;
	t_thread_args	*thread_args;

	if (!parse_input(argc, argv, &params))
		return (1);
	philos = malloc(sizeof(t_philo) * params.philo_number);
	forks = malloc(sizeof(pthread_mutex_t) * params.philo_number);
	has_eaten = malloc(sizeof(t_control) * params.philo_number);
	program = malloc(sizeof(t_program));
	program->dead_flag = false;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->forks_state_mutex, NULL);
	program->start_time = get_current_time();
	i = 0;
	thread_args = malloc(sizeof(t_thread_args) * params.philo_number);
	while (i < params.philo_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&has_eaten[i].mutex, NULL);
		i++;
	}
	program->start_time = get_current_time();
	i = 0;
	while (i < params.philo_number)
	{
		thread_args[i].params = params;
		thread_args[i].philo = &philos[i];
		thread_args[i].program = program;
		philos[i].left = i;
		if (i + 1 == params.philo_number)
			philos[i].right = 0;
		else
			philos[i].right = i + 1;
		launch_philo(params, i, &philos[i], forks, has_eaten, &thread_args[i]);
		i++;
	}
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag)
		{
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&program->dead_lock);
		usleep(100);
	}
	join_threads(philos, params);
	destroy_mutex(params, forks, has_eaten, program);
	free_mallocs(program, forks, has_eaten, thread_args, philos);
	return (0);
}
