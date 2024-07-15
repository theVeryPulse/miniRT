/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:05:52 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 00:58:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "window.h"
#include <math.h>

void	minirt_init()
{
	minirt()->image_aspect_ratio = (double)WIDTH / (double)HEIGHT;
	minirt()->fov = 90;
	minirt()->background_color = BLACK;
	minirt()->scale = tan(minirt()->fov * 0.5 * DEG_TO_RAD);
	minirt()->eye_canvas_distance = minirt()->eye_canvas_distance = (WIDTH / 2)
		/ tan((minirt()->fov / 2) * DEG_TO_RAD);
}
