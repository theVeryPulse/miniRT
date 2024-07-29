/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_light_from_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:06:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 18:26:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../object/inc/object.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

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
		printf("Error: unrecognised light type: %s\n", ptr);
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

	iter = line;
	if (ft_strncmp("A ", line, 2) == 0)
		iter += 2;
	skip_spaces(&iter);
	*a = ambient_light(ft_atof(iter));
	if (a->intensity < 0.0 || a->intensity > 1.0)
	{
		printf("Error: ambient light intensity out of range [0, 1]: %f\n",
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

	ptr = line;
	if (ft_strncmp("L ", line, 2) == 0 || ft_strncmp("l ", line, 2) == 0)
		ptr += 2;
	skip_spaces(&ptr);

	/* Load coordinate */
	position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	position.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	position.z = ft_atof(ptr);
	/* Load coordinate ends */

	skip_number(&ptr);
	skip_spaces(&ptr);
	intensity = ft_atof(ptr);
	*l = point_light(position, intensity);
	if (l->intensity < 0.0 || l->intensity > 1.0)
	{
		printf("Error: point light intensity out of range [0, 1]: %f\n",
			l->intensity);
		l->error = true;
	}
}
