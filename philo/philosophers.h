/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:08:32 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:54:43 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_manager	t_manager;
typedef struct s_philo		t_philo;
typedef struct s_philo
{
	int				philo_id;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_meals;
	int				num_of_eaten_meals;
	int				phil_dead;
	time_t			time_from_last_meal;
	pthread_mutex_t	personal_mutex;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_manager		*manager;
}	t_philo;

typedef struct s_manager
{
	int				nbr_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_of_meals;
	int				finished_meals_by_all;
	int				dead;
	time_t			start_time;
	t_philo			*arr_of_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	pthread_mutex_t	grim_mutex;
	pthread_t		grim_onlooker;
	pthread_t		*ptr_to_bodies;
}	t_manager;

int				check_argv(int argc, char *argv[]);
int				declaration_manager(t_manager *manager, int argc, char *argv[]);
int				declaration_philosophers(t_manager *manager);
int				create_threads(t_manager *manager);
int				init_mutex(t_manager *manager);
void			*routine(void *philo);
void			*grim_onlooker(void *manager);
int				chekc_if_philo_dead(t_manager *grim);

// lib functions
int				ft_atol(const char *nptr);
int				ft_isdigit(char *argv);
time_t			get_time(void);
// cleaner functions
void			clean_mutex_forks(pthread_mutex_t *arr, int i);
void			clean_helper(pthread_mutex_t *arr, int i, t_manager *manager);
void			clear_personal_mutexes(t_manager *manager, int i);
void			clean_personal_threads(t_manager *manager, pthread_t *bodies, \
																		int *i);
void			clean_full_manager(pthread_mutex_t *arr, int i, \
											t_manager *manager);
void			clear_manager_and_philos(t_manager *manager);
void			free_all(t_manager *manager);
// error handler
void			p_err(int i);
// routine helper functions
int				philo_meal_allowence(t_philo *philo);
void			special_sleep(time_t duration, t_philo *philo);
void			printf_forks(t_philo *philo);
void			odd_first_delay(t_philo *philo);
void			one_philo_function(t_philo *philo);
int				take_fork(t_philo *philo);
int				philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
// get info functions
int				global_grim_dead_f(t_manager *manager);
int				philo_dead_f(t_philo *philo);
int				exit_thread(t_philo *philo);
// get time functions
time_t			get_time_to_eat(t_philo *philo);
time_t			time_since_last_meal(t_philo *p);
time_t			get_local_time(t_manager *manager);
// grim routiine
void			raise_philo_dead_flag(t_philo *p);
int				killer_funcion(t_manager *grim);

#endif
