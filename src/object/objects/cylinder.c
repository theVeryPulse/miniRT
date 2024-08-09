/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:07:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	cylinder(t_argb color,
					t_raw_point position,
					t_vector direction,
					double radius,
					double height,
					double specular_exponent,
					double reflectivity)
{
	t_object	cylinder;

	cylinder = (t_object){0};
	cylinder.category = Object;
	cylinder.type = Cylinder;
	cylinder.color = color;
	cylinder.position = vec_mult(minirt()->unit_one, position);
	cylinder.direction = direction;
	cylinder.radius = radius * minirt()->unit_one;
	cylinder.radius_squared = cylinder.radius * cylinder.radius;
	cylinder.height = height * minirt()->unit_one;
	cylinder.specular_exponent = specular_exponent;
	cylinder.reflectivity = reflectivity;
	cylinder.is_checkerboard = false;
	cylinder.error = false;
	return (cylinder);
}
