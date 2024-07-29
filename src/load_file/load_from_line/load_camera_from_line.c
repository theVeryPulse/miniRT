/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:03:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 18:27:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../t_camera.h"
#include "../../minirt.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>
#include <stdbool.h>

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
	const char	*ptr;

	ptr = line;
	if (ft_strncmp("C ", line, 2) == 0)
		ptr += 2;

	skip_spaces(&ptr);

	/* load coordinate */
	camera->position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->position.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->position.z = ft_atof(ptr);
	/* load coordinate ends */

	skip_number(&ptr);
	skip_spaces(&ptr);

	/* load vector */
	camera->w.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->w.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->w.z = ft_atof(ptr);
	skip_number(&ptr);
	/* load vector ends */

	skip_spaces(&ptr);

	minirt()->fov = ft_atof(ptr);
	if (minirt()->fov < 0.0 || minirt()->fov > 180.0)
	{
		printf("Error: camera field of view out of range (0, 180): %f\n",
			minirt()->fov);
		camera->error = true;
	}
	if (camera->w.x == 0.0 && camera->w.y == 0.0 && camera->w.z == 0.0)
	{
		printf("Error: camera direction vector cannot be zero.\n");
		camera->error = true;
	}
}
