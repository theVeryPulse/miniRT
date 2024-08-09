/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:41:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

// clang-format off

t_object colored_sphere(t_argb      color,
                        t_raw_point position,
                        double      radius,
                        double      specular_exponent,
                        double      reflectivity)
{
    t_object sphere;

    sphere = (t_object){0};
    sphere.type = Sphere;
    sphere.category = Object;
    sphere.color = color;
    sphere.position = vec_mult(minirt()->unit_one, position);
    sphere.radius = radius * minirt()->unit_one;
    sphere.radius_squared = sphere.radius * sphere.radius;
    sphere.specular_exponent = specular_exponent;
    sphere.reflectivity = reflectivity;
    sphere.is_checkerboard = false;
    sphere.error = false;
    return (sphere);
}
