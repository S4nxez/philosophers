
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:18:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/24 23:18:41 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/**
 * @param action 1 for sleep, 2 for think, 3 for eat
 * @param philo id from philosopher
 * @param finished 1 for action finished 0 for action started
 */
void	philo_print(int action, int philo, int finished)
{
	char			*str;
	long			ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (action == 1)
		str = "sleep";
	else if (action == 2)
		str = "think";
	else if (action == 3)
		str = "eat";
	if (finished == 0)
		printf("[%ld] Philosopher %d is %sing\n", ms, philo, str);
	else
		printf("[%ld] Philosopher %d has finished %sing\n", ms, philo, str);
}
