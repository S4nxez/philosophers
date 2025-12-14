/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:23:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/08 20:04:47 by dansanc3         ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		death_thread;
	int				id;
	int				eating;
	int				times_eaten;
	long			last_meal;
	size_t			start_time;
	bool			dead;
	long			born;
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

typedef enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	philo_action_t;

typedef struct s_control
{
	bool			stop;
	pthread_mutex_t	mutex;
} t_control;

void	*philo_functions(void *params_void);
void	*death_detector_launcher(void *params_void);
long	philo_print(philo_action_t action, int philo);
bool	is_number(char *arg);
long	get_current_time(void);
long	get_philo_elapsed_time(t_philo philo);

#endif
