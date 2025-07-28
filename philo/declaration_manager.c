/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:26 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:02:58 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_manager(t_manager *manager)
{
	manager->nbr_philo = 0;
	manager->time_to_die = 0;
	manager->time_to_eat = 0;
	manager->time_to_sleep = 0;
	manager->num_of_meals = 0;
	manager->finished_meals_by_all = 0;
	manager->dead = 0;
	manager->start_time = get_time();
	manager->forks = NULL;
	manager->arr_of_philos = NULL;
	manager->ptr_to_bodies = NULL;
}

int	declaration_manager(t_manager *manager, int argc, char *argv[])
{
	init_manager(manager);
	manager->nbr_philo = ft_atol(argv[1]);
	if (manager->nbr_philo <= 0)
		return (0);
	manager->time_to_die = ft_atol(argv[2]);
	if (manager->time_to_die <= 0)
		return (0);
	manager->time_to_eat = ft_atol(argv[3]);
	if (manager->time_to_eat <= 0)
		return (0);
	manager->time_to_sleep = ft_atol(argv[4]);
	if (manager->time_to_sleep <= 0)
		return (0);
	if (argc == 6)
		manager->num_of_meals = ft_atol(argv[5]);
	if (argc == 6 && manager->num_of_meals <= 0)
		return (0);
	return (1);
}
