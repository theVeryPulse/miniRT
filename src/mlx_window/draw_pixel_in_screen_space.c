/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_in_screen_space.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:52:28 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:59:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_vars.h"
#include "../t_pixel.h"
#include "../window.h"

/* Defined in draw_pixel_in_raster_space.c */

extern void draw_pixel_in_raster_space(t_img_vars* img_vars, t_pixel pixel);

/**
 * @brief Draws a pixel in screen space. Screen space is centered at the middle
 *        of the window.
 *        Range: x = [-WIDTH / 2, WIDTH / 2], y = [-HEIGHT / 2, HEIGHT / 2].
 *
 * @param img_vars
 * @param pixel
 */
void draw_pixel_in_screen_space(t_img_vars* img_vars, t_pixel pixel)
{
    t_pixel converted;

    converted = (t_pixel){
        .x = WIDTH / 2 + pixel.x, .y = HEIGHT / 2 - pixel.y, pixel.color};
    draw_pixel_in_raster_space(img_vars, converted);
}
