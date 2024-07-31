/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:12 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 21:39:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	plane(t_p p)
{
	t_object	plane;

	plane = (t_object){0};
	plane.category = Object;
	plane.type = Plane;
	plane.color = p.color;
	plane.position = vec_mult(minirt()->unit_one, p.position);
	plane.direction = p.direction;
	plane.specular_exponent = p.specular_exponent;
	plane.reflectivity = p.reflectivity;
	plane.radius = -1;
	plane.error = false;
	return (plane);
}
