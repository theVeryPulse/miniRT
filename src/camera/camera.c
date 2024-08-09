/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:42:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:34:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"
#include "../minirt.h"
#include "t_camera.h"

/**
 * @brief
 *
 * @param position
 * @param w z-axis (pointing towards viewer) of the camera
 * @return t_camera
 */
t_camera camera(t_raw_point position, t_vector w)
{
    t_camera camera;

    camera          = (t_camera){0};
    camera.position = vec_mult(minirt()->unit_one, position);
    if (w.x == 0 && w.z == 0 && w.y > 0)
    {
        camera.u = (t_vector){1, 0, 0};
        camera.v = (t_vector){0, 0, -1};
        camera.w = (t_vector){0, 1, 0};
        return (camera);
    }
    else if (w.x == 0 && w.z == 0 && w.y < 0)
    {
        camera.u = (t_vector){1, 0, 0};
        camera.v = (t_vector){0, 0, 1};
        camera.w = (t_vector){0, -1, 0};
        return (camera);
    }
    camera.w = vec_normalized(w);
    camera.v = (t_vector){0, 1, 0};
    camera.u = vec_cross(camera.v, camera.w);
    camera.v = vec_cross(camera.w, camera.u);
    return (camera);
}
