/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:46 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:08:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	disk(t_argb color,
				t_raw_point position,
				t_vector direction,
				double radius,
				double specular_exponent,
				double reflectivity)
{
	t_object	disk;

	disk = (t_object){0};
	disk.category = Object;
	disk.type = Disk;
	disk.radius = radius * minirt()->unit_one;
	disk.radius_squared = disk.radius * disk.radius;
	disk.color = color;
	disk.position = vec_mult(minirt()->unit_one, position);
	disk.direction = direction;
	disk.specular_exponent = specular_exponent;
	disk.reflectivity = reflectivity;
	disk.error = false;
	return (disk);
}
