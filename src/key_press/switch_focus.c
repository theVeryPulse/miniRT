/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_focus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:09:41 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:46:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_vars.h"
#include "../../lib/minilibx-linux/mlx.h"

/* Functions defined in other files */

extern void put_image_to_window_vars(t_vars* vars);

/* Functions in this file */

static char* focus_message(t_object* focus);

/**
 * @brief
 *
 * @param vars
 */
extern void switch_focus(t_vars* vars)
{
    if (vars->scene.focus->category == Object
        && vars->scene.focus - vars->scene.objects
               >= vars->scene.object_count - 1)
        vars->scene.focus = vars->scene.lights;
    else if (vars->scene.focus->category == Light
             && vars->scene.focus - vars->scene.lights
                    >= vars->scene.light_count - 1)
        vars->scene.focus = vars->scene.objects;
    else
        ++(vars->scene.focus);
    put_image_to_window_vars(vars);
    mlx_string_put(vars->mlx_ptr, vars->win_ptr, 10, 10, GREEN,
                   focus_message(vars->scene.focus));
}

static char* focus_message(t_object* focus)
{
    if (focus->type == PointLight)
        return ("Focus: Point Light");
    else if (focus->type == DirectionalLight)
        return ("Focus: Directional Light");
    else if (focus->type == AmbientLight)
        return ("Focus: Ambience Light ");
    else if (focus->type == Sphere)
        return ("Focus: Sphere");
    else if (focus->type == Plane)
        return ("Focus: Plane");
    else if (focus->type == Disk)
        return ("Focus: Disk");
    else if (focus->type == Cylinder)
        return ("Focus: Cylinder");
    else
        return ("Unrecognized focus type");
}
