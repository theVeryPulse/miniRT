/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cylinder_from_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:45:06 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 13:48:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
#include "load_rgb.h"
#include "../skip/inc/skip.h"
#include "../../minirt.h"
#include "../../object/inc/object.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

/* Specular Exponent: range [1, INFINITY], normal objects are within [5, 20] */
#ifndef SPEC_EXPO
# define SPEC_EXPO 20.0
#endif

/* Reflectivity: range [0, 1] */
#ifndef REFLECT
# define REFLECT 0.1
#endif

#define RED_ERROR "\033[91merror: \033[0m"

/* External function */

extern void			load_cylinder_from_line(t_object *c, const char *line);

/* Helper functions */

static t_raw_point	bottom_center(t_raw_point center, t_vector axis,
						double height);
static void			print_cylinder_overview(t_object *c, t_raw_point center,
						double radius, double height);
static void			check_cylinder(t_object *c, double radius, double height);

/**
 * @brief 
 * 
 * @param c 
 * @param line 
 * @note
 * cylinder line format: 'cy', coordinate of center, axis vector, diameter,
 *                       height, rgb
 * cy 50.0,0.0,20.6     0,0,1.0      14.2  21.42    10,0,255
 */
extern void	load_cylinder_from_line(t_object *c, const char *line)
{
	t_raw_point	center;
	t_vector	axis;
	double		radius;
	double		height;

	printf("\nCylinder\n");
	if (ft_strncmp("cy ", line, 3) == 0)
		line += 2;
	skip_spaces(&line);
	load_point(&center, &line);
	skip_spaces(&line);
	load_vector(&axis, &line);
	vec_normalize(&axis);
	skip_spaces(&line);
	radius = ft_atof(line) / 2;
	skip_number(&line);
	skip_spaces(&line);
	height = ft_atof(line);
	skip_number(&line);
	skip_spaces(&line);
	*c = cylinder((t_c){(t_argb){0}, bottom_center(center, axis, height), axis,
			radius, height, SPEC_EXPO, REFLECT});
	print_cylinder_overview(c, center, radius, height);
	load_rgb(&(c->color), &line);
	check_cylinder(c, radius, height);
}

static t_raw_point	bottom_center(t_raw_point center, t_vector axis,
						double height)
{
	return (vec_minus(center, vec_mult(height / 2, axis)));
}

static void	print_cylinder_overview(t_object *c, t_raw_point center,
		double radius, double height)
{
	printf("  center: (%.1f, %.1f, %.1f), axis: (%.1f, %.1f, %.1f), "
		"radius: %.1f, height: %.1f\n", center.x, center.y, center.z,
		c->direction.x, c->direction.y, c->direction.z, radius, height);
}

static void	check_cylinder(t_object *c, double radius, double height)
{
	if (radius <= 0)
	{
		printf("  "RED_ERROR"invalid radius: %.1f\n", radius);
		c->error = true;
	}
	if (height <= 0)
	{
		printf("  "RED_ERROR"invalid height: %.1f\n", c->height);
		c->error = true;
	}
	if (c->direction.x == 0.0 && c->direction.y == 0.0 && c->direction.z == 0.0)
	{
		printf("  "RED_ERROR"axis vector cannot be zero.\n");
		c->error = true;
	}
}
