/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:42:57 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:43:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_vars.h"
#include "../window.h"
#include "../../lib/minilibx-linux/mlx.h"

extern void	set_up_mlx(t_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	vars->img_vars.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	vars->img_vars.addr = mlx_get_data_addr(vars->img_vars.img_ptr,
			&(vars->img_vars.bits_per_pixel), &(vars->img_vars.line_size),
			&(vars->img_vars.endian));
}
