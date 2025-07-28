/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:31:20 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 19:00:48 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argv(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("correct input: time-die, time-eat, time-sleep, " \
			"(optional)num-meals\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]) || !ft_atol(argv[i]))
		{
			printf("correct input: time-die, time-eat, time-sleep, " \
					"(optional)num-meals\n");
			return (0);
		}
		i++;
	}
	return (1);
}
