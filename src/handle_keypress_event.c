/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:20 by Philip            #+#    #+#             */
/*   Updated: 2024/07/25 19:43:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "../lib/minilibx-linux/mlx.h"
#include "minirt.h"
#include "../lib/libft/inc/libft.h"
#include <X11/keysym.h> /* XK_escape */
#include <stdio.h>
#include <stdlib.h> /* free */

void	put_image_to_window_vars(t_vars *vars);
int		clean_exit(int exit_status);
void	render_image(t_vars *vars);

static void	switch_focus(t_vars *vars)
{
	char	*message;

	if (vars->scene.focus->category == Object && vars->scene.focus
		- vars->scene.objects >= vars->scene.object_count - 1)
		vars->scene.focus = vars->scene.lights;
	else if (vars->scene.focus->category == Light && vars->scene.focus
		- vars->scene.lights >= vars->scene.light_count - 1)
		vars->scene.focus = vars->scene.objects;
	else
		++(vars->scene.focus);
	if (vars->scene.focus->type == PointLight)
		message = "Focus: Point Light";
	else if (vars->scene.focus->type == DirectionalLight)
		message = "Focus: Directional Light";
	else if (vars->scene.focus->type == AmbientLight)
		message = "Focus: Ambience Light ";
	else if (vars->scene.focus->type == Sphere)
		message = "Focus: Sphere";
	else if (vars->scene.focus->type == Plane)
		message = "Focus: Plane";
	else if (vars->scene.focus->type == Disk)
		message = "Focus: Disk";
	else if (vars->scene.focus->type == Cylinder)
		message = "Focus: Cylinder";
	else
		message = "What?";
	put_image_to_window_vars(vars);
	mlx_string_put(vars->mlx_ptr, vars->win_ptr, 10, 10, GREEN, message);
}

static void	adjust_directional_light(t_object *focus, int key)
{
	if (key == XK_Up)
		focus->direction.y += 0.2;
	else if (key == XK_Down)
		focus->direction.y -= 0.2;
	else if (key == XK_Left)
		focus->direction.x -= 0.2;
	else if (key == XK_Right)
		focus->direction.x += 0.2;
	else if (key == XK_i)
		focus->direction.z -= 0.2;
	else if (key == XK_o)
		focus->direction.z += 0.2;
}

static void	move_position(t_object *focus, int key)
{
	if (key == XK_Up)
		focus->position.y += 100;
	else if (key == XK_Down)
		focus->position.y -= 100;
	else if (key == XK_Left)
		focus->position.x -= 100;
	else if (key == XK_Right)
		focus->position.x += 100;
	else if (key == XK_i)
		focus->position.z -= 100;
	else if (key == XK_o)
		focus->position.z += 100;
}

static void	adjust_light_intensity(t_object *light, int key)
{
	double	factor;

	if (light->category != Light)
		return ;
	if (key == XK_Page_Up && light->intensity < 1)
		factor = 1.05;
	else
		factor = 0.95;
	light->intensity *= factor;
	if (light->intensity >= 1)
		light->intensity = 1;
}

extern int	handle_keypress_event(int key, t_vars *vars)
{
	t_object	*focus;

	focus = vars->scene.focus;
	printf("%d pressed\n", key);
	if (key == XK_Escape)
		clean_exit(0);
	else if (key == XK_Tab)
		switch_focus(vars);
	else if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right
		|| key == XK_i || key == XK_o
		|| key == XK_Page_Up || key == XK_Page_Down)
	{
		if (focus->type == DirectionalLight)
			adjust_directional_light(focus, key);
		else
			move_position(focus, key);
		if (focus->category == Light
			&& (key == XK_Page_Up || key == XK_Page_Down))
			adjust_light_intensity(focus, key);
		render_image(vars);
		put_image_to_window_vars(vars);
	}
	else if (key == XK_bracketleft || key == XK_bracketright)
	{
		if (key == XK_bracketleft)
			update_fov(minirt()->fov - 1);
		else if (key == XK_bracketright)
			update_fov(minirt()->fov + 1);
		render_image(vars);
		put_image_to_window_vars(vars);
		char *fov = ft_itoa((int)minirt()->fov);
		char *message = ft_format_string("FOV: %s");
		mlx_string_put(vars->mlx_ptr, vars->win_ptr, 10, 10, GREEN, message);
		free(fov);
		free(message);
	}
	return (0);
}
