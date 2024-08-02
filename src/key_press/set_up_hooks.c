/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:27:29 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:36:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_press_helpers.h"
#include "../minirt.h"
#include "../t_vars.h"
#include "../../lib/minilibx-linux/mlx.h"
#include <X11/X.h> /* DestroyNotify, ButtonReleaseMask */
#include <X11/keysym.h> /* XK_escape */
#include <stdio.h>
#include <stdlib.h> /* exit */

/* Defined in ./handle_keypress_event.c */

extern int	handle_keypress_event(int key, t_vars *vars);

void	set_up_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, handle_keypress_event, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, clean_exit,
		vars);
}
