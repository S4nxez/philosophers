/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:10:23 by dansanc3          #+#    #+#             */
/*   Updated: 2026/02/06 22:32:04 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	use_single_fork(t_philo *philo, t_program *program)
{
	pthread_mutex_lock(philo->left_fork);
	philo_print(FORK, philo->id, program, get_current_time());
	while (!is_dead(program))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	use_forks(t_philo *philo, t_program *program)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork == philo->right_fork)
		return (use_single_fork(philo, program));
	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	philo_print(FORK, philo->id, program, get_current_time());
	pthread_mutex_lock(second);
	philo_print(FORK, philo->id, program, get_current_time());
	return (1);
}

void	free_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
