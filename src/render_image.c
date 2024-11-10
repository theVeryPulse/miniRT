/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:02:33 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:47:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "t_pixel.h"
#include "ray/t_ray.h"
#include "window.h"
#include "minirt.h"
#include "geometry/inc/geometry.h"
#include "cast_ray/inc/cast_ray.h"
#include "mlx_window/inc/mlx_manage.h"
#include "../lib/minilibx-linux/mlx.h"
#include <math.h>

static t_vector transform_ray(t_camera* cam, t_point pt);
static void     draw_progress_line(t_img_vars* img_vars, int y);

/**
 * @brief
 * @ref computer-graphics-from-scratch / 02-basic-raytracing
 */
void render_image(t_vars* vars)
{
    t_ray   ray;
    t_pixel pixel;

    pixel.y = HEIGHT / 2;
    while (pixel.y > -HEIGHT / 2)
    {
        pixel.x = -WIDTH / 2;
        while (pixel.x < WIDTH / 2)
        {
            ray.origin = vars->scene.camera.position;
            ray.direction = transform_ray(
                &(vars->scene.camera),
                (t_point){pixel.x, pixel.y, -(minirt()->eye_canvas_distance)});
            ray.t_min = vec_len(ray.direction);
            ray.t_max = INFINITY;
            vec_normalize(&ray.direction);
            pixel.color = cast_ray(&vars->scene, &ray, 3);
            draw_pixel_in_screen_space(&vars->img_vars, pixel);
            ++pixel.x;
        }
        --pixel.y;
        draw_progress_line(&vars->img_vars, pixel.y);
        put_image_to_window_vars(vars);
    }
}

/**
 * @brief
 *
 * @param cam
 * @param pt
 * @return t_vector
 * @note
 * dx = (ux)(dx)
 */
static t_vector transform_ray(t_camera* cam, t_point pt)
{
    t_vector ray;

    ray.x = cam->u.x * pt.x + cam->v.x * pt.y + cam->w.x * pt.z;
    ray.y = cam->u.y * pt.x + cam->v.y * pt.y + cam->w.y * pt.z;
    ray.z = cam->u.z * pt.x + cam->v.z * pt.y + cam->w.z * pt.z;
    return (ray);
}

static void draw_progress_line(t_img_vars* img_vars, int y)
{
    t_pixel pixel;

    pixel.color = GREEN;
    pixel.y = y - 1;
    if (pixel.y <= -HEIGHT / 2)
        return;
    pixel.x = -WIDTH / 2;
    while (pixel.x < WIDTH / 2)
    {
        draw_pixel_in_screen_space(img_vars, pixel);
        ++pixel.x;
    }
}
