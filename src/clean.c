/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/12/13 19:53:34 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_program(t_program *p)
{
	if (!p)
		return ;
	free(p->philos);
	free(p->forks);
	free(p);
}

void	free_mallocs(t_program *program, pthread_mutex_t *forks,
		t_philo *philos)
{
	free(program);
	free(forks);
	free(philos);
}

void	join_threads(t_philo *philos, t_params params)
{
	int	i;

	i = 0;
	while (i < params.philo_number)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_join(philos[i].death_thread, NULL);
		i++;
	}
}

void	destroy_mutex(t_params params, pthread_mutex_t *forks,
			t_program *program)
{
	int	i;

	i = 0;
	while (i < params.philo_number)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

void	wait_ready(t_program *program)
{
	while (1)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (program->ready)
		{
			pthread_mutex_unlock(&program->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&program->dead_lock);
		usleep(50);
	}
}
