/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:05 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/24 12:16:26 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_manager	manager;

	if (!check_argv(argc, argv))
		return (1);
	if (!declaration_manager(&manager, argc, argv))
		return (1);
	if (!init_mutex(&manager))
		return (1);
	if (!declaration_philosophers(&manager))
		return (1);
	if (!create_threads(&manager))
		return (1);
	free_all(&manager);
	return (0);
}
