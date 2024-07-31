/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_div.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:35:33 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 22:21:00 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "stdio.h"

#define ORANGE_WARNING "\033[93mwarning: \033[0m"

extern t_vector	vec_div(t_vector a, double t)
{
	if (t == 0)
	{
		printf(ORANGE_WARNING"vec_div: zero division\n");
		return ((t_point){0});
	}
	return (vec_mult(1 / t, a));
}
