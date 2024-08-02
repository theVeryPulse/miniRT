/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_disk_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:34:07 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 23:31:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_closest.h"
#include "../ray/t_ray.h"
#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"

bool	ray_disk_intersect(
			t_ray *ray,
			t_object *disk,
			t_closest *closest)
{
	double		denominator;
	t_vector	intersect;
	t_vector	center_to_intersect;
	double		distance_squared;
	double		t;

	denominator = vec_dot(disk->direction, ray->direction);
	if (!equals(denominator, 0.0))
	{
		t = vec_dot(vec_minus(disk->position, ray->origin), disk->direction)
			/ denominator;
		intersect = vec_add(ray->origin, vec_mult(t, ray->direction));
		center_to_intersect = vec_minus(intersect, disk->position);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= disk->radius_squared
			&& t >= ray->t_min && t <= ray->t_max && t < closest->t)
		{
			closest->t = t;
			closest->object = disk;
			closest->object->backside = denominator < 0;
			return (true);
		}
	}
	return (false);
}
