/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_in_raster_space.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:51:08 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:57:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_vars.h"
#include "../t_pixel.h"
#include "../window.h"
#include <stdio.h> /* printf */
#include <stddef.h> /* ptrdiff_t */

/**
 * @brief Draws a pixel with the specified color at the given raster space
 *        coordinates on the mlx image.
 *        Raster space range: x = [0, WIDTH - 1], y = [0, HEIGHT - 1].
 *
 * @param img_vars Pointer to the image variables structure.
 * @param pixel The struct with coordinates and color of the pixel to draw.
 */
void	draw_pixel_in_raster_space(t_img_vars *img_vars, t_pixel pixel)
{
	char		*dst;
	ptrdiff_t	offset;

	if (pixel.x >= WIDTH || pixel.x < 0 || pixel.y >= HEIGHT || pixel.y < 0)
	{
		printf("(%d, %d) outside window\n", pixel.x, pixel.y);
		return ;
	}
	offset = pixel.y * img_vars->line_size
		+ pixel.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = pixel.color;
}
