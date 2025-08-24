/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/24 23:48:58 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philo(t_params *params, int i, pthread_t *thread)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->id = i;
	struct {
		t_params *params;
		t_philo *philo;
	} *thread_args = malloc(sizeof(*thread_args));
	thread_args->params = params;
	thread_args->philo = new_philo;

	pthread_create(thread, NULL, philo_functions,
		(void *)thread_args);
}

/**
 * Check that the input contains only numbers, they should all be bigger than 0
 * except the number of meals each philo needs to eat (edge case).
 * set the limit not to be more than 200.
 */
int	parse_input(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
		return (1);
	
	params->philo_number = atoi(argv[1]);
	params->time_to_starve = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		params->max_meals = atoi(argv[5]);
	return (0);

}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;
	int			i;

	if (parse_input(argc, argv, &params))
		return (1);
	philos = malloc(sizeof(t_philo) * params.philo_number);
	i = 0;
	while (i < params.philo_number)
	{
		launch_philo(&params, i + 1, &philos[i].thread);
		philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < params.philo_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (0);
}
