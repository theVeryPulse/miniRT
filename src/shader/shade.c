/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:41:38 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 18:14:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shade_helpers.h"
#include "../color/inc/argb.h"
#include "../geometry/inc/geometry.h"
#include "../t_closest.h"
#include "../ray/t_ray.h"
#include "../cast_ray/inc/cast_ray.h"
#include "../tracer/inc/trace.h"
#include "../scene/inc/scene.h"
#include <stddef.h>
#include <math.h>

extern t_argb	get_checkerboard_sphere_color(t_point pt, t_argb color1,
					t_argb color2);

static t_argb	get_local_color(t_object *object, t_point intersection,
			double intensity)
{
	t_argb	local_color;

	if (object->is_checkerboard && object->type == Sphere)
		local_color = get_checkerboard_sphere_color(
				vec_minus(intersection, object->position), WHITE, BLACK);
	else
		local_color = object->color;
	local_color = color_mult(local_color, intensity);
	return (local_color);
}

t_argb	shade(t_scene *scene, t_ray *ray, t_closest *closest,
			uint8_t recursion_depth)
{
	t_point		intersection;
	t_vector	unit_normal;
	double		intensity;
	t_argb		local_color;

	intersection = vec_add(ray->origin, vec_mult(closest->t, ray->direction));
	unit_normal = normal_on_surface(closest->object, intersection);
	intensity = calculate_light_intensity(scene, intersection, unit_normal,
			vec_mult(-1, ray->direction), closest->object->specular_exponent);
	local_color = get_local_color(closest->object, intersection, intensity);
	// return (local_color); /* Return color here to skip reflection */
	/* When recursion limit is hit or the other object does not reflect */
	if (recursion_depth <= 0 || closest->object->reflectivity <= 0)
		return (local_color);
	/* Else computes reflected color */
	t_ray	reflection_ray;
	t_argb	reflected_color;

	reflection_ray.origin = intersection;
	reflection_ray.direction = reflect_ray(
		vec_mult(-1, ray->direction), unit_normal);
	reflection_ray.t_min = 0.001;
	reflection_ray.t_max = INFINITY;
	reflected_color = cast_ray(scene, &reflection_ray, recursion_depth - 1);
	/* The more smooth the object is, the more light it reflects */
	return (color_add(
		color_mult(local_color, 1 - closest->object->reflectivity),
		color_mult(reflected_color, closest->object->reflectivity)));
}
