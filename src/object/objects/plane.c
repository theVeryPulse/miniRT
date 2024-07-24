/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:12 by Philip            #+#    #+#             */
/*   Updated: 2024/07/22 19:23:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	plane(
	t_argb color,
	t_point position,
	t_vector direction,
	double specular_exponent,
	double reflectivity
)
{
	return ((t_object){
		.category = Object,
		.type = Plane,
		.color = color,
		.position = position,
		.direction = direction,
		.specular_exponent = specular_exponent,
		.reflectivity = reflectivity,
		.radius = -1.0
	});
}
