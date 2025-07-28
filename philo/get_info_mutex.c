/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:35:56 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:38:05 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_dead_f(t_philo *philo)
{
	int	phil_dead;

	phil_dead = 0;
	pthread_mutex_lock(&philo->personal_mutex);
	phil_dead = philo->phil_dead;
	pthread_mutex_unlock(&philo->personal_mutex);
	return (phil_dead);
}

int	global_grim_dead_f(t_manager *manager)
{
	int	global_dead;

	pthread_mutex_lock(&manager->grim_mutex);
	global_dead = manager->dead;
	pthread_mutex_unlock(&manager->grim_mutex);
	return (global_dead);
}

time_t	get_time_to_eat(t_philo *philo)
{
	time_t	time_to_eat;

	pthread_mutex_lock(&philo->personal_mutex);
	time_to_eat = philo->time_to_eat;
	pthread_mutex_unlock(&philo->personal_mutex);
	return (time_to_eat);
}
