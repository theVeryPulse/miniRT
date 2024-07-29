/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:08:40 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 00:13:05 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
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

static int	load_rgb(t_argb *rgb, const char **line);
static void	load_sphere_from_line(t_object *object, const char *line);

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
	{
	}
	else if (ft_strncmp("cy ", line, 3) == 0)
	{
	}
	else
	{
	}
}

static int	load_rgb(t_argb *rgb, const char **line)
{
	int	red;
	int	green;
	int	blue;
	int	error;

	error = 0;
	red = ft_atoi(*line);
	*line = ft_strchr(*line, ',') + 1;
	green = ft_atoi(*line);
	*line = ft_strchr(*line, ',') + 1;
	blue = ft_atoi(*line);
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
		error = printf("  "RED_ERROR"rgb out of range [0, 255]: %d,%d,%d\n",
				red, green, blue);
	*rgb = argb(0xFF, (uint8_t)red, (uint8_t)green, (uint8_t)blue);
	return (error > 0);
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
	else
		printf("  color: %d,%d,%d\n", red_component(sphere->color),
			green_component(sphere->color), blue_component(sphere->color));
	if (radius <= 0 && printf("  "RED_ERROR"invalid radius: %.1f\n", radius))
		sphere->error = true;
}
