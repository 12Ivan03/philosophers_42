/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:26 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 10:38:43 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo_function(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	printf_forks(philo);
	special_sleep(philo->time_to_die, philo);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_lock(&philo->personal_mutex);
	philo->phil_dead = 1;
	pthread_mutex_unlock(&philo->personal_mutex);
}
