/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:01 by Philip            #+#    #+#             */
/*   Updated: 2024/07/25 22:15:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	cylinder(
	t_argb color,
	t_raw_point position,
	t_vector direction,
	double radius,
	double height,
	double specular_exponent,
	double reflectivity)
{
	t_object	cylinder;

	cylinder.category = Object;
	cylinder.type = Cylinder;
	cylinder.color = color;
	cylinder.position = vec_mult(minirt()->unit_one, position);
	cylinder.direction = direction;
	cylinder.radius = radius * minirt()->unit_one;
	cylinder.height = height * minirt()->unit_one;
	cylinder.specular_exponent = specular_exponent;
	cylinder.reflectivity = reflectivity;
	cylinder.is_checkerboard = false;
	return (cylinder);
}
