/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light_intensity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:06:08 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 16:46:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shade_helpers.h"
#include "../ray/t_ray.h"
#include "../tracer/inc/trace.h"
#include "../t_closest.h"
#include "../scene/t_scene.h"
#include "../geometry/inc/geometry.h"
#include <math.h>
#include <stddef.h>

static bool	light_is_blocked(t_scene *scene, t_ray shadow_ray)
{
	t_closest	closest;

	closest.object = NULL;
	closest.t = INFINITY;
	shadow_ray.t_min = 1e-4;
	if (trace(scene, &shadow_ray, &closest))
		return (true);
	else
		return (false);
}

/**
 * @brief Computes the intensity of reflection at given point, including diffuse
 *        reflection, specular reflection, shade,
 * 
 * @param scene Scene struct, which contains all light sources.
 * @param point Point on object to calculate.
 * @param normal Normal vector at the point on surface.
 * @param view 
 * @param specular_exponent 
 * @return double Intensity of the diffuse light at given point, range [0, 1]
 * @note
 * For point light, t_max is 1, this means object on the other side of the light
 * will not cast shadow on current object.
 */
double	calculate_light_intensity(t_scene *scene, t_point point, t_vector normal,
		t_vector view, double specular_exponent)
{
	t_object	*light;
	double		intensity;
	double		normal_dot_light;
	t_ray		shadow_ray;

	intensity = 0.0;
	light = scene->lights;
	shadow_ray = (t_ray){.origin = point, .t_min = 1e-4, .t_max = INFINITY};
	while (light < scene->light_count + scene->lights)
	{
		if (light->type == AmbientLight)
			intensity += light->intensity;
		else
		{
			if (light->type == PointLight)
			{
				shadow_ray.direction = vec_minus(light->position, point);
				shadow_ray.t_max = vec_len(shadow_ray.direction);
				vec_normalize(&shadow_ray.direction);
			}
			else if (light->type == DirectionalLight)
			{
				shadow_ray.direction = light->direction;
				shadow_ray.t_max = INFINITY;
			}

			if (light_is_blocked(scene, shadow_ray))
			{
				++light;
				continue;
			}

			/* Diffuse reflection */
			normal_dot_light = vec_dot(normal, shadow_ray.direction);
			if (normal_dot_light > 0)
				intensity += light->intensity * normal_dot_light
					/ (vec_len(normal) * vec_len(shadow_ray.direction));
			
			/* Specular reflection */
			if (specular_exponent > 0.0)
			{
				t_vector	reflection;
				double		reflection_dot_view;

				reflection = reflect_ray(shadow_ray.direction, normal);
				reflection_dot_view = vec_dot(reflection, view);
				if (reflection_dot_view > 0)
				{
					intensity += light->intensity
						* pow(reflection_dot_view
						/ (vec_len(reflection) * vec_len(view)),
						specular_exponent);
				}
			}
		}
		++light;
	}
	if (intensity >= 1)
		intensity = 1;
	return (intensity);
}