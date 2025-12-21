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
	pthread_mutex_t *forks, t_control *has_eaten, t_program *program)
{
	t_thread_args	*thread_args;

	philo->id = i;
	thread_args = malloc(sizeof(t_thread_args));
	thread_args->params = params;
	thread_args->philo = philo;
	philo->times_eaten = 0;
	philo->dead = 0;
	philo->last_meal = 0;
	philo->born = get_current_time();
	pthread_mutex_init(&forks[i], NULL);
	philo->left_fork = &forks[i];
	if (i + 1 == params.philo_number)
		philo->right_fork = &forks[0];
	else
		philo->right_fork = &forks[i + 1];
	pthread_mutex_init(&has_eaten[i].mutex, NULL);
	has_eaten[i - 1].stop = false;
	thread_args->has_eaten = &has_eaten[i - 1];
	thread_args->program = program;
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
	params->time_to_starve = 1000 * ft_atoi(argv[2]);
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

	if (!parse_input(argc, argv, &params))
		return (1);
	philos = malloc(sizeof(t_philo) * params.philo_number);
	forks = malloc(sizeof(pthread_mutex_t) * params.philo_number);
	has_eaten = malloc(sizeof(t_control) * params.philo_number);
	program = malloc(sizeof(t_program));
	program->dead_flag = false;
	pthread_mutex_init(&program->dead_lock, NULL);
	program->fork_state = malloc(sizeof(t_fork_state) * params.philo_number);
	memset(program->fork_state, FREE, sizeof(t_fork_state)
		* params.philo_number);
	pthread_mutex_init(&program->forks_state_mutex, NULL);
	i = 0;
	while (i < params.philo_number)
	{
		philos[i].left = i;
		if (i + 1 == params.philo_number)
			philos[i].right = 0;
		else
			philos[i].right = i + 1;
		launch_philo(params, i + 1, &philos[i], forks, has_eaten, program);
		i++;
	}
	i = 0;
	while (!program->dead_flag)
		usleep(500);
	while (i < params.philo_number)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_join(philos[i].death_thread, NULL);
		i++;
	}
	while (i < params.philo_number)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&has_eaten[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	free(program->fork_state);
	free(program);
	free(forks);
	free(has_eaten);
	free(philos);
	return (0);
}
