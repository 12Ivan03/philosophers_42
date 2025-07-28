/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration_philosophers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:04:33 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/27 13:33:38 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *arr_philo, t_manager *manager, int i)
{
	arr_philo->philo_id = i + 1;
	arr_philo->time_to_die = manager->time_to_die;
	arr_philo->time_to_eat = manager->time_to_eat;
	arr_philo->time_to_sleep = manager->time_to_sleep;
	arr_philo->num_of_meals = manager->num_of_meals;
	arr_philo->num_of_eaten_meals = 0;
	arr_philo->phil_dead = manager->dead;
	arr_philo->time_from_last_meal = get_time();
	arr_philo->left_f = &manager->forks[i];
	arr_philo->right_f = &manager->forks[(i + 1) % manager->nbr_philo];
	arr_philo->manager = manager;
}

int	init_personal_mutex_in_philo(t_manager *m)
{
	int	i;

	i = 0;
	while (i < m->nbr_philo)
	{
		if (pthread_mutex_init(&m->arr_of_philos[i].personal_mutex, NULL) != 0)
			return (clear_personal_mutexes(m, i), 1);
		i++;
	}
	return (0);
}

int	declaration_philosophers(t_manager *manager)
{
	t_philo	*arr_philo;
	int		i;

	arr_philo = (t_philo *)malloc(manager->nbr_philo * sizeof(t_philo));
	if (arr_philo == NULL)
		return (clean_full_manager(manager->forks, \
				manager->nbr_philo - 1, manager), 0);
	i = 0;
	while (i < manager->nbr_philo)
	{
		init_philo(&arr_philo[i], manager, i);
		i++;
	}
	manager->arr_of_philos = arr_philo;
	if (init_personal_mutex_in_philo(manager))
		return (0);
	return (1);
}
