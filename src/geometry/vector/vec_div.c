/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_div.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:35:33 by Philip            #+#    #+#             */
/*   Updated: 2024/07/23 19:44:57 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "stdio.h"

extern t_vector	vec_div(t_vector a, double t)
{
	if (t == 0)
	{
		printf("Warning[vec_div]: zero division");
		return ((t_point){0});
	}
	return (vec_mult(1 / t, a));
}
