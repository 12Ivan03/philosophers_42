/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:30:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/21 12:43:55 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_err(int i)
{
	if (i == 1)
		printf("Error with initialising the env\n");
	else if (i == 2)
		printf("Error mutext uninitialized\n");
	else if (i == 3)
		printf("Error creating philosopher\n");
}
