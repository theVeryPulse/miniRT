/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:08:40 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 19:55:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
#include "load_rgb.h"
#include "load_cylinder_from_line.h"
#include "../skip/inc/skip.h"
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

extern void	load_object_from_line(t_object *object, const char *line);

static void	load_sphere_from_line(t_object *sphere, const char *line);
static void	load_plane_from_line(t_object *plane, const char *line);

/**
 * @brief 
 * 
 * @param object 
 * @param line 
 */
extern void	load_object_from_line(t_object *object, const char *line)
{
	skip_spaces(&line);
	if (ft_strncmp("sp ", line, 3) == 0)
		load_sphere_from_line(object, line);
	else if (ft_strncmp("pl ", line, 3) == 0)
		load_plane_from_line(object, line);
	else if (ft_strncmp("cy ", line, 3) == 0)
		load_cylinder_from_line(object, line);
	else
	{
	}
}

/**
 * @brief 
 * 
 * @param object 
 * @param line 
 * @note
 * sphere line format: 'sp', coordinate, radius, rgb
 * Example:
 * sp 0,0,20                         20             255,0,0
 */
static void	load_sphere_from_line(t_object *sphere, const char *line)
{
	t_raw_point	position;
	double		radius;

	if (ft_strncmp("sp ", line, 3) == 0)
		line += 2;
	skip_spaces(&line);
	load_point(&position, &line);
	skip_spaces(&line);
	radius = ft_atof(line);
	skip_number(&line);
	skip_spaces(&line);
	printf("\nSphere\n  position: (%.1f,%.1f,%.1f), radius: %.1f\n",
		position.x, position.y, position.z, radius);
	*sphere = colored_sphere((t_argb){0}, position, radius, SPEC_EXPO, REFLECT);
	if (load_rgb(&(sphere->color), &line) != 0)
		sphere->error = true;
	if (radius <= 0 && printf("  "RED_ERROR"invalid radius: %.1f\n", radius))
		sphere->error = true;
}

/**
 * @brief 
 * 
 * @param plane 
 * @param line 
 * @note
 * plane line format: 'pl', coordinate, normal vector, rgv
 * pl 0,0,0             0,1.0,0                     255,0,225
 */
static void	load_plane_from_line(t_object *p, const char *line)
{
	t_raw_point	position;
	t_vector	normal;

	if (ft_strncmp("pl ", line, 3) == 0)
		line += 2;
	skip_spaces(&line);
	load_point(&position, &line);
	skip_spaces(&line);
	load_vector(&normal, &line);
	skip_spaces(&line);
	printf("\nPlane\n  position: (%.1f, %.1f, %.1f), "
		"normal: (%.1f, %.1f, %.1f)\n",
		position.x, position.y, position.z, normal.x, normal.y, normal.z);
	*p = plane((t_argb){0}, position, normal, SPEC_EXPO, REFLECT);
	if (load_rgb(&(p->color), &line) != 0)
		p->error = true;
	if (p->direction.x == 0.0 && p->direction.y == 0.0 && p->direction.z == 0.0)
	{
		printf("  "RED_ERROR"normal vector cannot be zero.\n");
		p->error = true;
	}
}
