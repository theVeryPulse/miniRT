/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/06/28 21:27:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include "vars.h"
#include "window.h"
#include <X11/X.h> /* DestroyNotify, ButtonReleaseMask */
#include <X11/keysym.h> /* XK_escape */

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

int	destroy_exit(t_vars *vars)
{
	printf("exiting...\n");
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	exit (0);
}

int	handle_key(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
}

void	set_up_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, handle_key, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit,
		vars);
}

void	set_up_mlx(t_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	vars->img_vars.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	vars->img_vars.addr = mlx_get_data_addr(vars->img_vars.img_ptr,
			&(vars->img_vars.bits_per_pixel), &(vars->img_vars.line_size),
			&(vars->img_vars.endian));
}

/**
 * @brief Puts the image to the window.
 *
 * @param vars Pointer to the variables structure.
 */
void	put_image_to_window_vars(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		vars->img_vars.img_ptr, 0, 0);
}

#include "pixel.h"
#include <stddef.h>
/**
 * @brief Draws a pixel with the specified color at the given raster space
 *        coordinates on the mlx image.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param pixel The struct with coordinates and color of the pixel to draw.
 */
void	draw_pixel_in_raster_space(t_img_vars *img_vars, t_pixel pixel)
{
	char		*dst;
	ptrdiff_t	offset;

	if (pixel.x >= WIDTH || pixel.x < 0 || pixel.y >= HEIGHT || pixel.y < 0)
		return ;
	offset = pixel.y * img_vars->line_size
		+ pixel.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = pixel.color;
}

void	draw_pixel_in_screen_space(t_img_vars *img_vars, t_pixel pixel)
{
	t_pixel	converted;

	converted = (t_pixel){.x = WIDTH / 2 + pixel.x,
		.y = HEIGHT / 2 - pixel.y, pixel.color};
	draw_pixel_in_raster_space(img_vars, converted);
}

void	test_draw_on_image(t_img_vars *img_vars)
{
	t_pixel	pixel;

	pixel.color = WHITE;
	pixel.y = 0;
	for	(pixel.x = - WIDTH / 2; pixel.x <= WIDTH / 2; ++pixel.x)
		draw_pixel_in_screen_space(img_vars, pixel);
	pixel.x = 0;
	for	(pixel.y = -HEIGHT / 2; pixel.y <= HEIGHT / 2; ++pixel.y)
		draw_pixel_in_screen_space(img_vars, pixel);	
}

int	main(int argc, char const *argv[])
{
	t_vars	vars;

	set_up_mlx(&vars);
	set_up_hooks(&vars);
	test_draw_on_image(&(vars.img_vars));
	put_image_to_window_vars(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
