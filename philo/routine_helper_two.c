/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:35:54 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/27 13:09:11 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_messages(t_philo *p, char *str)
{
	if (chekc_if_philo_dead(p->manager))
		return ;
	pthread_mutex_lock(&p->manager->printf);
	printf("%ld %d %s\n", get_local_time(p->manager), p->philo_id, str);
	pthread_mutex_unlock(&p->manager->printf);
}

int	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_f);
		print_messages(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_f);
	}
	else
	{
		pthread_mutex_lock(philo->left_f);
		print_messages(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_f);
	}
	print_messages(philo, "has taken a fork");
	return (1);
}

int	philo_eat(t_philo *p)
{
	time_t	time_to_eat;

	time_to_eat = get_time_to_eat(p);
	pthread_mutex_lock(&p->personal_mutex);
	p->time_from_last_meal = get_time();
	pthread_mutex_unlock(&p->personal_mutex);
	print_messages(p, "is eating");
	special_sleep(time_to_eat, p);
	if (p->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(p->right_f);
		pthread_mutex_unlock(p->left_f);
	}
	else
	{
		pthread_mutex_unlock(p->left_f);
		pthread_mutex_unlock(p->right_f);
	}
	pthread_mutex_lock(&p->personal_mutex);
	p->num_of_eaten_meals++;
	pthread_mutex_unlock(&p->personal_mutex);
	return (0);
}

void	philo_sleep(t_philo *p)
{
	print_messages(p, "is sleeping");
	special_sleep(p->time_to_sleep, p);
}

void	philo_think(t_philo *p)
{
	print_messages(p, "is thinking");
	if (p->manager->nbr_philo % 2 == 1 && p->philo_id % 2 == 1)
		usleep(1000);
	else
		usleep(200);
}
