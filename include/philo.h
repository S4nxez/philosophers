/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/06 20:50:41 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_params
{
	int				philo_number;
	int				time_to_starve;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
}					t_params;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void	*philo_functions(void *params_void);
void	p_sleep(int time_to_sleep, t_philo philo);
void	think(int time_to_think, t_philo philo);
void	eat(int time_to_eat, t_philo philo,
	pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork);
void	philo_print(int action, int philo, int finished);
bool	is_number(char *arg);

#endif
