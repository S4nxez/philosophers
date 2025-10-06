/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/06 20:55:43 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philo(t_params *params, int i, pthread_t *philo,
	pthread_mutex_t *forks)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->id = i;
	struct {
		t_params		*params;
		t_philo			*philo;
		pthread_mutex_t	*left_fork;
		pthread_mutex_t	*right_fork;
	} *thread_args = malloc(sizeof(*thread_args));
	thread_args->params = params;
	thread_args->philo = new_philo;

	pthread_mutex_init(&forks[i], NULL);
	thread_args->left_fork = &forks[i];
	thread_args->right_fork = &forks[i - 1];
	pthread_create(philo, NULL, philo_functions, (void *)thread_args);
}

/**
 * input contains only numbers,
 * all bigger than 0 except the number of meals each philo needs to eat
 * not to more than 200 philos.
 */
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
	if (atoi(argv[1]) > 200)
		return (false);
	params->philo_number = atoi(argv[1]);
	params->time_to_starve = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		params->max_meals = atoi(argv[5]);
	return (true);

}

int	main(int argc, char **argv)
{
	t_params		params;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;

	if (!parse_input(argc, argv, &params))
		return (1);
	philos = malloc(sizeof(t_philo) * params.philo_number);
	forks = malloc(sizeof(pthread_mutex_t) * params.philo_number);
	i = 0;
	while (i < params.philo_number)
	{
		launch_philo(&params, i + 1, &philos[i].thread, forks);
		philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < params.philo_number)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	free(philos);
	return (0);
}
