/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:30:36 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:08:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_OBJECT_H
#define T_OBJECT_H

#include "../geometry/vector/t_point.h"
#include "../color/inc/argb.h"
#include <stdbool.h>

typedef enum e_category
{
    UndefinedCategory,
    Camera,
    Object,
    Light
} t_category;

typedef enum e_object_type
{
    UndefinedObject,
    CameraType,
    Sphere,
    Plane,
    Disk,
    Cylinder,
    AmbientLight,
    PointLight,
    DirectionalLight
} t_object_type;

typedef enum e_intersect
{
    UndefinedIntersect,
    BottomFace,
    TopFace,
    CurvedSurface
} t_intersect;

typedef struct s_object
{
    /* Common properties */
    bool          error;
    t_category    category;
    t_object_type type;
    t_point       position;

    /* All light sources */
    double intensity;
    /* Direction for directional light.
    Normal for plane.
    Axis for cylinder. */
    t_vector direction;
    /* Sphere, disk, cylinder */
    double radius;
    double radius_squared;
    /* All objects */
    double specular_exponent;
    /* All objects */
    double reflectivity;
    /* All objects */
    t_argb color;
    /* Spheres */
    bool is_checkerboard;
    /* Plane, disk */
    bool backside;
    /* Cylinder */
    double height;
    /* Cylinder */
    t_intersect ray_intersects;
} t_object;

#endif /* T_OBJECT_H */