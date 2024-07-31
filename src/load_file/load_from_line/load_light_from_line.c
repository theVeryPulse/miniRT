/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_light_from_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:06:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 03:44:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
#include "load_rgb.h"
#include "../skip/inc/skip.h"
#include "../../object/inc/object.h"
#include "../../minirt.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

#define RED_ERROR "\033[91merror: \033[0m"

extern void	load_light_from_line(t_object *object, const char *line);

static void	load_ambient_light_from_line(t_object *a, const char *line);
static void	load_point_light_from_line(t_object *l, const char *line);

/**
 * @brief 
 * 
 * @param object 
 * @param line 
 */
extern void	load_light_from_line(t_object *object, const char *line)
{
	const char	*ptr;

	ptr = line;
	skip_spaces(&ptr);
	if (ft_strncmp("A ", ptr, 2) == 0)
		load_ambient_light_from_line(object, ptr);
	else if (ft_strncmp("L ", ptr, 2) == 0)
		load_point_light_from_line(object, ptr);
	else if (ft_strncmp("l ", ptr, 2) == 0)
		load_point_light_from_line(object, ptr);
	else
		printf(RED_ERROR"unrecognised light type: %s\n", ptr);
}

/**
 * @brief 
 * 
 * @param line 
 * @return t_object 
 * @note
 * Ambient light format: 'A', intensity, rgb
 * Example:
 * A  0.2                                         255,255,255   
 * 
 */
static void	load_ambient_light_from_line(t_object *a, const char *line)
{
	const char	*iter;

	printf("\nAmbient Light\n");
	iter = line;
	if (ft_strncmp("A ", line, 2) == 0)
		iter += 2;
	skip_spaces(&iter);
	*a = ambient_light(ft_atof(iter));
	printf("  intensity: %.1f\n", a->intensity);
	if (a->intensity < 0.0 || a->intensity > 1.0)
	{
		printf("  "RED_ERROR"intensity out of range [0, 1]: %.1f\n",
			a->intensity);
		a->error = true;
	}
}

/**
 * @brief 
 * 
 * @param pl 
 * @param line 
 * @note
 * Point light format: 'L', coordinate, intensity, rgb
 * Example:
 *     L -40,0,30                        0.7            255,255,255
 * 
 */
static void	load_point_light_from_line(t_object *l, const char *line)
{
	const char	*ptr;
	t_raw_point	position;
	double		intensity;

	printf("\nPoint Light\n");
	ptr = line;
	if (ft_strncmp("L ", line, 2) == 0 || ft_strncmp("l ", line, 2) == 0)
		ptr += 2;
	skip_spaces(&ptr);
	load_point(&position, &ptr);
	skip_spaces(&ptr);
	intensity = ft_atof(ptr);
	printf("  position: (%.1f, %.1f, %.1f), intensity: %.1f\n",
		position.x, position.y, position.z, intensity);
	*l = point_light(position, intensity);
	if (l->intensity < 0.0 || l->intensity > 1.0)
	{
		printf("  "RED_ERROR"point light intensity out of range [0, 1]: %.1f\n",
			l->intensity);
		l->error = true;
	}
}
