/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:16:24 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 23:32:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_intersect.h"
#include "../scene/t_scene.h"
#include "../t_closest.h"
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
bool	trace(t_scene *scene, t_ray *ray, t_closest *closest)
{
	t_object	*object;

	closest->object = NULL;
	object = scene->objects;
	ray->direction_squared = vec_dot(ray->direction, ray->direction);
	while (object < scene->object_count + scene->objects)
	{
		if (object->type == Sphere)
			ray_sphere_intersect(ray, object, closest);
		else if (object->type == Plane)
			ray_plane_intersect(ray, object, closest);
		else if (object->type == Disk)
			ray_disk_intersect(ray, object, closest);
		else if (object->type == Cylinder)
			ray_cylinder_intersect(ray, object, closest);
		++object;
	}
	return (closest->object != NULL);
}
