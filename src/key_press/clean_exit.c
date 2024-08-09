/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:26:03 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:45:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "../t_vars.h"
#include "../../lib/minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h> /* exit */

int clean_exit(int exit_status)
{
    t_vars* vars;

    vars = minirt()->vars;
    printf("exiting...\n");
    mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
    mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
    mlx_destroy_display(vars->mlx_ptr);
    free(vars->mlx_ptr);
    if (vars->scene.objects)
        free(vars->scene.objects);
    if (vars->scene.lights)
        free(vars->scene.lights);
    exit(exit_status);
}
