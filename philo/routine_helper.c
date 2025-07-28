/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:26 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/27 13:31:00 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_forks(t_philo *philo)
{
	if (chekc_if_philo_dead(philo->manager))
		return ;
	pthread_mutex_lock(&philo->manager->printf);
	printf("%ld %d has taken a fork\n", get_local_time(philo->manager), \
														philo->philo_id);
	pthread_mutex_unlock(&philo->manager->printf);
}

int	philo_meal_allowence(t_philo *philo)
{
	int	num_meals_philo;

	pthread_mutex_lock(&philo->personal_mutex);
	num_meals_philo = philo->num_of_eaten_meals;
	pthread_mutex_unlock(&philo->personal_mutex);
	if (philo->manager->num_of_meals != 0 && \
		num_meals_philo == philo->manager->num_of_meals)
	{
		pthread_mutex_lock(&philo->manager->grim_mutex);
		philo->manager->finished_meals_by_all++;
		pthread_mutex_unlock(&philo->manager->grim_mutex);
	}
	return (0);
}

int	exit_thread(t_philo *philo)
{
	if (philo_dead_f(philo) == 1)
		return (1);
	if (global_grim_dead_f(philo->manager) == 1)
		return (1);
	return (0);
}

void	special_sleep(time_t duration, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while (duration > get_time() - start && \
		!chekc_if_philo_dead(philo->manager))
	{
		if (global_grim_dead_f(philo->manager) || philo_dead_f(philo))
			break ;
		usleep(500);
	}
}

void	odd_first_delay(t_philo *philo)
{
	time_t	time_left_to_die;

	time_left_to_die = philo->time_to_die - time_since_last_meal(philo);
	if (time_left_to_die >= philo->time_to_eat * 1.5)
		usleep(philo->time_to_eat * 100);
}
