/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 19:02:00 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	colored_sphere(t_s s)
{
	t_object	sphere;

	sphere = (t_object){0};
	sphere.type = Sphere;
	sphere.category = Object;
	sphere.color = s.color;
	sphere.position = vec_mult(minirt()->unit_one, s.position);
	sphere.radius = s.radius * minirt()->unit_one;
	sphere.radius_squared = sphere.radius * sphere.radius;
	sphere.specular_exponent = s.specular_exponent;
	sphere.reflectivity = s.reflectivity;
	sphere.is_checkerboard = false;
	sphere.error = false;
	return (sphere);
}
