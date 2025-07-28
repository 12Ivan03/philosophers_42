/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_of_day.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:38:18 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_local_time(t_manager *manager)
{
	time_t	current_time;

	current_time = get_time() - manager->start_time;
	return (current_time);
}

time_t	get_time(void)
{
	struct timeval	get_time;
	time_t			time;

	gettimeofday(&get_time, NULL);
	time = ((get_time.tv_sec * 1000) + (get_time.tv_usec / 1000));
	return (time);
}

time_t	time_since_last_meal(t_philo *p)
{
	time_t	time;
	time_t	last_meal_t;

	pthread_mutex_lock(&p->personal_mutex);
	last_meal_t = p->time_from_last_meal;
	pthread_mutex_unlock(&p->personal_mutex);
	time = get_time() - last_meal_t;
	return (time);
}
