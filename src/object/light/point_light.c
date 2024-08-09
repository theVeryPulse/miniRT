/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:56:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:07:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"
#include "../../minirt.h"
#include "../../geometry/inc/geometry.h"

t_object point_light(t_raw_point position, double intensity)
{
    t_object point_light;

    point_light = (t_object){0};
    point_light.type = PointLight;
    point_light.category = Light;
    point_light.intensity = intensity;
    point_light.position = vec_mult(minirt()->unit_one, position);
    point_light.direction = (t_vector){0};
    point_light.radius = -1;
    point_light.error = false;
    return (point_light);
}
