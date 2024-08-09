/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_on_surface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:40:17 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:32:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"
#include "../t_closest.h"

static t_vector normal_on_cylinder_surface(
    t_object* cylinder, t_point intersection);

/**
 * @brief
 *
 * @param obj
 * @param intersection
 * @return t_vector
 */
extern t_vector normal_on_surface(t_object* obj, t_point intersection)
{
    if (obj->type == Sphere)
        return (vec_normalized(vec_minus(intersection, obj->position)));
    else if ((obj->type == Plane || obj->type == Disk) && !obj->backside)
        return (obj->direction);
    else if ((obj->type == Plane || obj->type == Disk) && obj->backside)
        return (vec_mult(-1, obj->direction));
    else if (obj->type == Cylinder)
        return (normal_on_cylinder_surface(obj, intersection));
    else
        return ((t_vector){0, 0, 0});
}

static t_vector normal_on_cylinder_surface(
    t_object* cylinder, t_point intersection)
{
    t_vector unit_normal;
    t_vector q;
    t_vector q_on_v;

    if (cylinder->ray_intersects == CurvedSurface)
    {
        q = vec_minus(intersection, cylinder->position);
        q_on_v = vec_mult(vec_dot(q, cylinder->direction), cylinder->direction);
        unit_normal = vec_normalized(vec_minus(q, q_on_v));
    }
    else if (
        cylinder->ray_intersects == BottomFace
        || cylinder->ray_intersects == TopFace)
    {
        unit_normal = cylinder->direction;
        if (cylinder->backside)
            unit_normal = vec_mult(-1, unit_normal);
    }
    return (unit_normal);
}
