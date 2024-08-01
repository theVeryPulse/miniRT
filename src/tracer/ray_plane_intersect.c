/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:26:36 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:30:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"

extern void	ray_plane_intersect(
	double *t,
	t_point ray_origin,
	t_vector ray_direction,
	t_object *plane,
	double t_min,
	double t_max,
	t_object **closest_object,
	double *closest_t)
{
	double	denominator;

	denominator = vec_dot(plane->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		*t = vec_dot(vec_minus(plane->position, ray_origin), plane->direction)
			/ denominator;
		if (*t >= t_min && *t <= t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = plane;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
		}
	}
}
