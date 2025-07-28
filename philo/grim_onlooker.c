/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_onlooker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:22 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/27 13:37:51 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	chekc_if_philo_dead(t_manager *grim)
{
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->dead == 1)
	{
		pthread_mutex_unlock(&grim->grim_mutex);
		return (1);
	}
	pthread_mutex_unlock(&grim->grim_mutex);
	return (0);
}

void	raise_philo_dead_flag(t_philo *p)
{
	pthread_mutex_lock(&p->personal_mutex);
	p->phil_dead = 1;
	pthread_mutex_unlock(&p->personal_mutex);
}

int	meal_allowence_grim_check(t_manager *grim)
{
	pthread_mutex_lock(&grim->grim_mutex);
	if (grim->num_of_meals != 0 && \
		grim->nbr_philo == grim->finished_meals_by_all)
	{
		grim->dead = 1;
		pthread_mutex_unlock(&grim->grim_mutex);
		return (0);
	}
	pthread_mutex_unlock(&grim->grim_mutex);
	return (1);
}

void	terminalte(t_manager *grim, int i)
{
	pthread_mutex_lock(&grim->grim_mutex);
	grim->dead = 1;
	pthread_mutex_unlock(&grim->grim_mutex);
	pthread_mutex_lock(&grim->printf);
	printf("%ld %d dead\n", get_time() - grim->start_time, i + 1);
	pthread_mutex_unlock(&grim->printf);
	pthread_mutex_unlock(&grim->printf);
	killer_funcion(grim);
	raise_philo_dead_flag(&grim->arr_of_philos[i]);
}

void	*grim_onlooker(void *manager)
{
	t_manager	*grim;
	int			i;

	i = 0;
	grim = (t_manager *)manager;
	while (!global_grim_dead_f(grim) && meal_allowence_grim_check(grim))
	{
		i = 0;
		while (i < grim->nbr_philo)
		{
			if (time_since_last_meal(&grim->arr_of_philos[i]) > \
										grim->time_to_die)
			{
				terminalte(grim, i);
				break ;
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
