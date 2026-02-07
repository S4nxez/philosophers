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
int	is_dead(t_program *program)
{
	int	val;

	pthread_mutex_lock(&program->dead_lock);
	val = program->dead_flag;
	pthread_mutex_unlock(&program->dead_lock);
	return (val);
}

long	philo_print(t_philo_action action, int philo, t_program *program,
		long ms)
{
	long	ts;

	ts = ms - program->start_time;
	pthread_mutex_lock(&program->dead_lock);
	if (!program->dead_flag)
	{
		if (action == DIE)
			program->dead_flag = true;
		pthread_mutex_lock(&program->write_lock);
		if (action == FORK)
			printf("%ld %d has taken a fork\n", ts, philo);
		else if (action == EAT)
			printf("%ld %d is eating\n", ts, philo);
		else if (action == SLEEP)
			printf("%ld %d is sleeping\n", ts, philo);
		else if (action == THINK)
			printf("%ld %d is thinking\n", ts, philo);
		else if (action == DIE)
			printf("%ld %d died\n", ts, philo);
		pthread_mutex_unlock(&program->write_lock);
	}
	pthread_mutex_unlock(&program->dead_lock);
	return (ms);
}

long	get_philo_elapsed_time(t_philo philo)
{
	if (philo.last_meal != 0)
		return (get_current_time() - philo.last_meal);
	else
		return (get_current_time() - philo.born);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time_us, t_program *program)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_us / 1000)
	{
		if (is_dead(program))
			return ;
		usleep(500);
	}
}
