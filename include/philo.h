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
	int				left;
	int				right;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_params
{
	int				philo_number;
	int				time_to_starve;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
}					t_params;

typedef enum e_fork_state
{
	FREE,
	TAKEN
}	t_fork_state;

typedef struct s_control
{
	bool			stop;
	pthread_mutex_t	mutex;
}	t_control;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks_state_mutex;
	long			start_time;
	pthread_mutex_t	*forks;
	t_control		*has_eaten;
	t_philo			*philos;
}					t_program;

typedef enum e_philo_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_philo_action;

typedef struct s_thread_args
{
	t_params		params;
	t_philo			*philo;
	t_control		*has_eaten;
	t_program		*program;
}	t_thread_args;

void			*philo_functions(void *params_void);
void			*death_detector_launcher(void *params_void);
long			philo_print(t_philo_action action, int philo,
					t_program *program, long ms);
bool			is_number(char *arg);
int				is_dead(t_program *program);
long			get_current_time(void);
void			ft_usleep(long time_us, t_program *program);
long			get_philo_elapsed_time(t_philo philo);
int				ft_atoi(const char *str);
void			free_mallocs(t_program *program, pthread_mutex_t *forks,
					t_control *has_eaten, t_philo *philos);
void			destroy_mutex(t_params params, pthread_mutex_t *forks,
					t_control *has_eaten, t_program *program);
void			join_threads(t_philo *philos, t_params params);
int				use_forks(t_philo philo, t_program *program);
void			free_forks(t_philo philo);
void			init_mutexs(t_program *program);
void			forks_launchers(t_params params, t_program *program);
t_thread_args	*launchers(t_params params, t_program *program);
void			launch_philo(int i, t_thread_args *thread_args);
#endif
