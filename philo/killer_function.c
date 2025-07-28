/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:40:25 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/24 12:16:41 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	killer_funcion(t_manager *grim)
{
	int	i;

	i = 0;
	while (i < grim->nbr_philo)
	{
		pthread_mutex_lock(&grim->arr_of_philos[i].personal_mutex);
		grim->arr_of_philos[i].phil_dead = 1;
		pthread_mutex_unlock(&grim->arr_of_philos[i].personal_mutex);
		i++;
	}
	return (0);
}
