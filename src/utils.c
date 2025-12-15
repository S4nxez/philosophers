/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:18:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/13 19:32:09 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param action the action the philosopher is doing
 * @param philo id from philosopher
 *
 * @return action timestamp
 */
long	philo_print(philo_action_t action, int philo, t_program *program)
{
	long	ms;

	ms = get_current_time();
	if (action == FORK && !program->dead_flag)
		printf("%ld %d has taken a fork\n", ms, philo);
	else if (action == EAT && !program->dead_flag)
		printf("%ld %d is eating\n", ms, philo);
	else if (action == SLEEP && !program->dead_flag)
		printf("%ld %d is sleeping\n", ms, philo);
	else if (action == THINK && !program->dead_flag)
		printf("%ld %d is thinking\n", ms, philo);
	else if (action == DIE && !program->dead_flag)
		printf("%ld %d died\n", ms, philo);
	return (ms);
}

long	get_philo_elapsed_time(t_philo philo)
{
	if (philo.last_meal != 0)
		return (philo.last_meal - get_current_time());
	else
		return (philo.born - get_current_time());
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
