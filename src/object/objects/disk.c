/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/25 22:20:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	disk(
	t_argb color,
	t_raw_point position,
	t_vector direction,
	double radius,
	double specular_exponent,
	double reflectivity
)
{
	t_object	disk;

	disk.category = Object;
	disk.type = Disk;
	disk.radius = radius * minirt()->unit_one;
	disk.color = color;
	disk.position = vec_mult(minirt()->unit_one, position);
	disk.direction = direction;
	disk.specular_exponent = specular_exponent;
	disk.reflectivity = reflectivity;
	return (disk);
}
