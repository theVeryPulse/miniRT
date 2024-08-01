/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:26:36 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 17:18:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ray/t_ray.h"
#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"

extern void	ray_plane_intersect(
	t_ray *ray,
	t_object *plane,
	t_object **closest_object,
	double *closest_t)
{
	double	denominator;
	double	t;

	denominator = vec_dot(plane->direction, ray->direction);
	if (!equals(denominator, 0.0))
	{
		t = vec_dot(vec_minus(plane->position, ray->origin), plane->direction)
			/ denominator;
		if (t >= ray->t_min && t <= ray->t_max && t < *closest_t)
		{
			*closest_t = t;
			*closest_object = plane;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
		}
	}
}
