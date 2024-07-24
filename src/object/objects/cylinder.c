/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:01 by Philip            #+#    #+#             */
/*   Updated: 2024/07/23 18:59:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	cylinder(
	t_argb color,
	t_point position,
	t_vector direction,
	double radius,
	double height,
	double specular_exponent,
	double reflectivity)
{
	return ((t_object){
		.category = Object,
		.type = Cylinder,
		.color = color,
		.position = position,
		.direction = direction,
		.radius = radius,
		.height = height,
		.specular_exponent = specular_exponent,
		.reflectivity = reflectivity,
		.is_checkerboard = false
	});
}
