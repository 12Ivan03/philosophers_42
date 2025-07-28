/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mutex_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:44:49 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:00:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_personal_threads(t_manager *manager, pthread_t *bodies, int *i)
{
	while ((*i) >= 0)
	{
		pthread_join(bodies[(*i)], NULL);
		(*i)--;
	}
	if (bodies)
	{
		free(bodies);
		bodies = NULL;
	}
	clear_manager_and_philos(manager);
}

void	free_all(t_manager *manager)
{
	int	i;

	i = 0;
	if (manager->ptr_to_bodies)
	{
		while (i < manager->nbr_philo)
		{
			pthread_join(manager->ptr_to_bodies[i], NULL);
			i++;
		}
		free(manager->ptr_to_bodies);
		manager->ptr_to_bodies = NULL;
	}
	pthread_join(manager->grim_onlooker, NULL);
	clear_manager_and_philos(manager);
}
