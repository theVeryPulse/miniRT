/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:41:38 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:31:34 by Philip           ###   ########.fr       */
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

static t_object build_tangent_plane(t_ray* ray, t_closest* closest);

static t_argb get_local_color(
    t_object* object, t_point intersection, double intensity);

/**
 * @brief
 *
 * @param scene
 * @param ray
 * @param closest
 * @param recursion_depth
 * @return t_argb
 */
t_argb shade(
    t_scene* scene, t_ray* ray, t_closest* closest, uint8_t recursion_depth)
{
    double   intensity;
    t_argb   local_color;
    t_ray    reflection_ray;
    t_argb   reflected_color;
    t_object tangent_plane;

    tangent_plane = build_tangent_plane(ray, closest);
    intensity = calculate_light_intensity(
        scene, &tangent_plane, vec_mult(-1, ray->direction));
    local_color = get_local_color(
        closest->object, tangent_plane.position, intensity);
    if (recursion_depth <= 0 || closest->object->reflectivity <= 0)
        return (local_color);
    reflection_ray = (t_ray){
        .origin = tangent_plane.position,
        .direction = reflect_ray(
            vec_mult(-1, ray->direction), tangent_plane.direction),
        .t_min = 0.001,
        .t_max = INFINITY};
    reflected_color = cast_ray(scene, &reflection_ray, recursion_depth - 1);
    return (color_add(
        color_mult(local_color, 1 - closest->object->reflectivity),
        color_mult(reflected_color, closest->object->reflectivity)));
}

static t_object build_tangent_plane(t_ray* ray, t_closest* closest)
{
    t_object plane;
    t_point  intersection;
    t_vector unit_normal;

    intersection = vec_add(ray->origin, vec_mult(closest->t, ray->direction));
    unit_normal = normal_on_surface(closest->object, intersection);
    plane = (t_object){0};
    plane.category = Object;
    plane.type = Plane;
    plane.position = intersection;
    plane.direction = unit_normal;
    plane.specular_exponent = closest->object->specular_exponent;
    plane.reflectivity = closest->object->reflectivity;
    plane.radius = -1;
    plane.error = false;
    return (plane);
}

static t_argb get_local_color(
    t_object* object, t_point intersection, double intensity)
{
    t_argb local_color;

    if (object->is_checkerboard && object->type == Sphere)
        local_color = get_checkerboard_sphere_color(
            vec_minus(intersection, object->position), WHITE, BLACK);
    else
        local_color = object->color;
    local_color = color_mult(local_color, intensity);
    return (local_color);
}
