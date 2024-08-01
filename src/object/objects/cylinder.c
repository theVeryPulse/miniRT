/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:49:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 13:50:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	cylinder(t_c c)
{
	t_object	cylinder;

	cylinder = (t_object){0};
	cylinder.category = Object;
	cylinder.type = Cylinder;
	cylinder.color = c.color;
	cylinder.position = vec_mult(minirt()->unit_one, c.position);
	cylinder.direction = c.direction;
	cylinder.radius = c.radius * minirt()->unit_one;
	cylinder.height = c.height * minirt()->unit_one;
	cylinder.specular_exponent = c.specular_exponent;
	cylinder.reflectivity = c.reflectivity;
	cylinder.is_checkerboard = false;
	cylinder.error = false;
	return (cylinder);
}
