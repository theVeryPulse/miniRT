/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:03:46 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:53:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
#include "load_rgb.h"
#include "../skip/inc/skip.h"
#include "../../camera/inc/camera.h"
#include "../../minirt.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>
#include <stdbool.h>

#define RED_ERROR "\033[91merror: \033[0m"

/**
 * @brief
 *
 * @param camera
 * @param line
 * @note
 * Camera line format: 'C', coordinate, angle vector, fov
 * Example:
 * C -50,0,20           0,0,1        70
 *
 */
extern void load_camera_from_line(t_camera* c, const char* line)
{
    printf("\nCamera\n");
    if (ft_strncmp("C ", line, 2) == 0)
        line += 2;
    skip_spaces(&line);
    load_point(&c->position, &line);
    skip_spaces(&line);
    load_vector(&c->w, &line);
    skip_spaces(&line);
    minirt()->fov = ft_atof(line);
    printf("  position: (%.1f, %.1f, %.1f), direction: (%.1f, %.1f, %.1f), "
           "fov: %.1f\n",
           c->position.x, c->position.y, c->position.z, c->w.x, c->w.y, c->w.z,
           minirt()->fov);
    *c = camera(c->position, c->w);
    if (minirt()->fov <= 0.0 || minirt()->fov >= 180.0)
    {
        printf("  " RED_ERROR "field of view out of range (0, 180): %.1f\n",
               minirt()->fov);
        c->error = true;
    }
    if (c->w.x == 0.0 && c->w.y == 0.0 && c->w.z == 0.0)
    {
        printf("  " RED_ERROR "direction vector cannot be zero.\n");
        c->error = true;
    }
}
