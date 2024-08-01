/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_color_sphere.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:11:32 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 15:02:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/vector/t_point.h"
#include "color/inc/argb.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#define CHECKERBOARD_CELL_COUNT 8

extern t_argb	get_checkerboard_sphere_color(t_point pt, t_argb color1,
					t_argb color2);

static void		convert_to_uv_texture_coordinates(t_point pt, double *u,
					double *v);
static bool		is_color1(double u, double v, uint8_t square_count);

extern t_argb	get_checkerboard_sphere_color(t_point pt, t_argb color1,
				t_argb color2)
{
	double	u;
	double	v;

	convert_to_uv_texture_coordinates(pt, &u, &v);
	if (is_color1(u, v, CHECKERBOARD_CELL_COUNT))
		return (color1);
	else
		return (color2);
}

static void	convert_to_uv_texture_coordinates(t_point pt, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = atan2(pt.z, pt.x);
	phi = acos(pt.y / sqrt(pt.x * pt.x + pt.y * pt.y + pt.z * pt.z));
	*u = (theta + M_PI) / (2 * M_PI);
	*v = phi / M_PI;
}

static bool	is_color1(double u, double v, uint8_t square_count)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(u * square_count);
	grid_y = (int)(v * square_count);
	if ((grid_x + grid_y) % 2 == 0)
		return (true);
	else
		return (false);
}
