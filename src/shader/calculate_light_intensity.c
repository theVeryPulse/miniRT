/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light_intensity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:06:08 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:43:45 by Philip           ###   ########.fr       */
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

// clang-format off

static t_ray build_shadow_ray(t_object* light, t_point point);

static bool light_is_blocked(t_scene* scene, t_ray shadow_ray);

static double reflection_intensity(
    t_object*       light,
    t_ray           shadow_ray,
    const t_object* tangent_plane,
    t_vector        view);

// clang-format on

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
double calculate_light_intensity(t_scene* scene, t_object* tangent_plane,
                                 t_vector view)
{
    t_object* light;
    double    intensity;
    t_ray     shadow_ray;

    intensity = 0.0;
    light = scene->lights;
    while (light < scene->light_count + scene->lights)
    {
        if (light->type == AmbientLight)
            intensity += light->intensity;
        else
        {
            shadow_ray = build_shadow_ray(light, tangent_plane->position);
            if (!light_is_blocked(scene, shadow_ray))
                intensity += reflection_intensity(light, shadow_ray,
                                                  tangent_plane, view);
        }
        ++light;
    }
    if (intensity >= 1)
        intensity = 1;
    return (intensity);
}

static t_ray build_shadow_ray(t_object* light, t_point point)
{
    t_ray shadow_ray;

    shadow_ray = (t_ray){.origin = point, .t_min = 1e-4, .t_max = INFINITY};
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
    return (shadow_ray);
}

static bool light_is_blocked(t_scene* scene, t_ray shadow_ray)
{
    t_closest closest;

    closest.object = NULL;
    closest.t = INFINITY;
    shadow_ray.t_min = 1e-4;
    if (trace(scene, &shadow_ray, &closest))
        return (true);
    else
        return (false);
}

static double reflection_intensity(t_object* light, t_ray shadow_ray,
                                   const t_object* tangent_plane, t_vector view)
{
    double   normal_dot_light;
    double   intensity;
    t_vector reflection;
    double   reflection_dot_view;

    intensity = 0.0;
    normal_dot_light = vec_dot(tangent_plane->direction, shadow_ray.direction);
    if (normal_dot_light > 0)
        intensity += light->intensity * normal_dot_light
                     / (vec_len(tangent_plane->direction)
                        * vec_len(shadow_ray.direction));
    if (tangent_plane->specular_exponent > 0.0)
    {
        reflection = reflect_ray(shadow_ray.direction,
                                 tangent_plane->direction);
        reflection_dot_view = vec_dot(reflection, view);
        if (reflection_dot_view > 0)
        {
            intensity += light->intensity
                         * pow(reflection_dot_view
                                   / (vec_len(reflection) * vec_len(view)),
                               tangent_plane->specular_exponent);
        }
    }
    return (intensity);
}
