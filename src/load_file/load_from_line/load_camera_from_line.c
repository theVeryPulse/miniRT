/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:03:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 19:46:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_vector.h"
#include "../skip/inc/skip.h"
#include "../../t_camera.h"
#include "../../minirt.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>
#include <stdbool.h>

#define RED_ERROR "\033[31mError: \033[0m"

/**
 * @brief 
 * 
 * @param camera 
 * @param line 
 * @note
 * Camera line format: 'C', coordinate, angle vector, fov
 * Example:
 * C -50,0,20           0,0,1        70
 * 
 */
extern void	load_camera_from_line(t_camera *camera, const char *line)
{
	if (ft_strncmp("C ", line, 2) == 0)
		line += 2;
	skip_spaces(&line);
	load_point(&camera->position, &line);
	skip_spaces(&line);
	load_vector(&camera->w, &line);
	skip_spaces(&line);
	minirt()->fov = ft_atof(line);
	printf("\nCamera\nposition: (%.1f, %.1f, %.1f), "
		"direction: (%.1f, %.1f, %.1f), fov: %.1f\n",
		camera->position.x, camera->position.y, camera->position.z,
		camera->w.x, camera->w.y, camera->w.z, minirt()->fov);
	if (minirt()->fov <= 0.0 || minirt()->fov >= 180.0)
	{
		printf(RED_ERROR"field of view out of range (0, 180): %.1f\n",
			minirt()->fov);
		camera->error = true;
	}
	if (camera->w.x == 0.0 && camera->w.y == 0.0 && camera->w.z == 0.0)
	{
		printf(RED_ERROR"direction vector cannot be zero.\n");
		camera->error = true;
	}
}
