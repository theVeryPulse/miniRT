/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:16:24 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 17:40:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_intersect.h"
#include "../scene/t_scene.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Checks if a ray hits any object, if hit, record this closest object
 *        and closest_t.
 * 
 * @param scene 
 * @param ray_origin 
 * @param ray_direction 
 * @param t_min 
 * @param t_max 
 * @param closest_object 
 * @param closest_t 
 * @return bool
 */
bool	trace(t_scene *scene,
	t_point ray_origin,
	t_vector ray_direction,
	double t_min,
	double t_max,
	t_object **closest_object,
	double *closest_t)
{
	t_object	*object;
	t_ray		ray;

	ray = (t_ray){ray_origin, ray_direction, t_min, t_max, 0};
	*closest_object = NULL;
	object = scene->objects;
	ray.direction_squared = vec_dot(ray_direction, ray_direction);
	while (object < scene->object_count + scene->objects)
	{
		if (object->type == Sphere)
			ray_sphere_intersect(&ray, object, closest_object, closest_t);
		else if (object->type == Plane)
			ray_plane_intersect(&ray, object, closest_object, closest_t);
		else if (object->type == Disk)
			ray_disk_intersect(&ray, object, closest_object, closest_t);
		else if (object->type == Cylinder)
			ray_cylinder_intersect(&ray, object, closest_object, closest_t);
		++object;
	}
	return (*closest_object != NULL);
}
