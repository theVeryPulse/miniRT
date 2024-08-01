/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_disk_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:34:07 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:35:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"

void	ray_disk_intersect(
			double *t,
			t_point ray_origin,
			t_vector ray_direction,
			t_object *disk,
			double t_min,
			double t_max,
			t_object **closest_object,
			double *closest_t)
{
	double		denominator;
	t_vector	intersect;
	t_vector	center_to_intersect;
	double		distance_squared;

	denominator = vec_dot(disk->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		*t = vec_dot(vec_minus(disk->position, ray_origin), disk->direction)
			/ denominator;
		intersect = vec_add(ray_origin, vec_mult(*t, ray_direction));
		center_to_intersect = vec_minus(intersect, disk->position);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= disk->radius_squared
			&& *t >= t_min && *t <= t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = disk;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
		}
	}
}
