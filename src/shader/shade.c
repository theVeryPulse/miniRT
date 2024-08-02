/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:41:38 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 03:05:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief 
 * 
 * @param normal 
 * @param ray 
 * @return t_vector 
 * @note Equation: R = 2 * dot(N, L) * N - L
 */
static inline t_vector	reflect_ray(t_vector ray, t_vector normal)
{
	return (vec_minus(vec_mult(2 * vec_dot(normal, ray), normal), ray));
}

/**
 * @brief Computes the intensity of reflection at given point, including diffuse
 *        reflection, specular reflection, shade,
 * 
 * @param scene Scene struct, which contains all light sources.
 * @param point Point on object to calculate.
 * @param normal Normal vector at the point on surface.
 * @return double Intensity of the diffuse light at given point, range [0, 1]
 * @note
 * For point light, t_max is 1, this means object on the other side of the light
 * will not cast shadow on current object.
 */
double	compute_lighting(t_scene *scene, t_point point, t_vector normal,
		t_vector view, double specular_exponent)
{
	size_t		i;
	double		intensity;
	t_vector	light;
	double		normal_dot_light;
	double		t_max;

	intensity = 0.0;
	i = 0;
	while (i < scene->light_count)
	{
		if (scene->lights[i].type == AmbientLight)
			intensity += scene->lights[i].intensity;
		else
		{
			if (scene->lights[i].type == PointLight)
			{
				light = vec_minus(scene->lights[i].position, point);
				t_max = vec_len(light);
				light = vec_normalized(light);
			}
			else if (scene->lights[i].type == DirectionalLight)
			{
				light = scene->lights[i].direction;
				t_max = INFINITY;
			}
			else /* Silencing gcc warning */
				t_max = INFINITY;

			/* Shadow check */
			t_ray		shadow_ray;
			t_closest	closest;
			
			closest.object = NULL;
			closest.t = INFINITY;
			shadow_ray.origin = point;
			shadow_ray.direction = light;
			shadow_ray.t_min = 1e-4;
			shadow_ray.t_max = t_max;
			if (trace(scene, &shadow_ray, &closest))
			{
				++i;
				continue;
			}

			/* Diffuse reflection */
			normal_dot_light = vec_dot(normal, light);
			if (normal_dot_light > 0)
				intensity += scene->lights[i].intensity * normal_dot_light
					/ (vec_len(normal) * vec_len(light));
			
			/* Specular reflection */
			if (specular_exponent > 0.0)
			{
				t_vector	reflection;
				double		reflection_dot_view;

				reflection = reflect_ray(light, normal);
				reflection_dot_view = vec_dot(reflection, view);
				if (reflection_dot_view > 0)
				{
					intensity += scene->lights[i].intensity
						* pow(reflection_dot_view
						/ (vec_len(reflection) * vec_len(view)),
						specular_exponent);
				}
			}
		}
		++i;
	}
	if (intensity >= 1)
		intensity = 1;
	return (intensity);
}

t_argb	shade(t_scene *scene, t_ray *ray, t_closest *closest,
			uint8_t recursion_depth)
{
	t_point		intersection;
	t_vector	unit_normal;
	double		intensity;
	t_argb		local_color;

	intersection = vec_add(ray->origin, vec_mult(closest->t, ray->direction));
	if (closest->object->type == Sphere)
		unit_normal = vec_normalized(
			vec_minus(intersection, closest->object->position));
	else if (closest->object->type == Plane || closest->object->type == Disk)
	{
		unit_normal = closest->object->direction;
		if (closest->object->backside)
			unit_normal = vec_mult(-1.0, unit_normal);
	}
	else if (closest->object->type == Cylinder)
	{
		if (closest->object->ray_intersects == CurvedSurface)
		{
			t_vector q = vec_minus(intersection, closest->object->position);
			t_vector q_on_v = vec_mult(vec_dot(q, closest->object->direction),
				closest->object->direction);
			unit_normal = vec_normalized(vec_minus(q, q_on_v));
		}
		else if (closest->object->ray_intersects == BottomFace
			|| closest->object->ray_intersects == TopFace)
		{
			unit_normal = closest->object->direction;
			if (closest->object->backside)
				unit_normal = vec_mult(-1, unit_normal);
		}
	}
	else
	{
	}
	intensity = compute_lighting(scene, intersection, unit_normal,
		vec_mult(-1, ray->direction), closest->object->specular_exponent);
	if (closest->object->is_checkerboard)
		local_color = color_mult(
			get_checkerboard_sphere_color(
				vec_minus(intersection, closest->object->position),
				WHITE,
				BLACK
			),
			intensity
		);
	else
		local_color = color_mult(closest->object->color, intensity);

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
