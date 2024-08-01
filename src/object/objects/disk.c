/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:46 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 19:01:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object	disk(t_d d)
{
	t_object	disk;

	disk = (t_object){0};
	disk.category = Object;
	disk.type = Disk;
	disk.radius = d.radius * minirt()->unit_one;
	disk.radius_squared = disk.radius * disk.radius;
	disk.color = d.color;
	disk.position = vec_mult(minirt()->unit_one, d.position);
	disk.direction = d.direction;
	disk.specular_exponent = d.specular_exponent;
	disk.reflectivity = d.reflectivity;
	disk.error = false;
	return (disk);
}
