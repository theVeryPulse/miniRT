/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:25:40 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 19:02:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	checkerboard_sphere(t_cs cs)
{
	t_object	sphere;

	sphere = (t_object){0};
	sphere.category = Object;
	sphere.type = Sphere;
	sphere.position = vec_mult(minirt()->unit_one, cs.position);
	sphere.radius = cs.radius * minirt()->unit_one;
	sphere.radius_squared = sphere.radius * sphere.radius;
	sphere.specular_exponent = cs.specular_exponent;
	sphere.reflectivity = cs.reflectivity;
	sphere.is_checkerboard = true;
	sphere.error = false;
	return (sphere);
}
