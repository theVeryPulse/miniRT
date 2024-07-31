/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:25:40 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 17:33:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	checkerboard_sphere(
	t_raw_point position,
	double radius,
	double specular_exponent,
	double reflectivity
)
{
	t_object	sphere;

	sphere = (t_object){0};
	sphere.category = Object;
	sphere.type = Sphere;
	sphere.position = vec_mult(minirt()->unit_one, position);
	sphere.radius = radius * minirt()->unit_one;
	sphere.specular_exponent = specular_exponent;
	sphere.reflectivity = reflectivity;
	sphere.is_checkerboard = true;
	sphere.error = false;
	return (sphere);
}
