/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:08:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object plane(t_argb      color,
               t_raw_point position,
               t_vector    direction,
               double      specular_exponent,
               double      reflectivity)
{
    t_object plane;

    plane = (t_object){0};
    plane.category = Object;
    plane.type = Plane;
    plane.color = color;
    plane.position = vec_mult(minirt()->unit_one, position);
    plane.direction = direction;
    plane.specular_exponent = specular_exponent;
    plane.reflectivity = reflectivity;
    plane.radius = -1;
    plane.error = false;
    return (plane);
}
