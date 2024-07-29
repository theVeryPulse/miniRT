/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:29:12 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 17:42:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_counter.h"
#include "check_line_components.h"
#include "../skip/skip.h"
#include "../../../lib/libft/inc/libft.h"

int	check_line(const char *iter, t_counter *count)
{
	int	line_error;

	line_error = 0;
	skip_spaces(&iter);
	if (ft_strncmp("\n", iter, 2) == 0)
		;
	else if (ft_strncmp("A ", iter, 2) == 0 && ++count->ambient_light)
		line_error |= check_ambient_light_line(&iter);
	else if (ft_strncmp("C ", iter, 2) == 0 && ++count->camera)
		line_error |= check_camera_line(&iter);
	else if (ft_strncmp("L ", iter, 2) == 0 && ++count->unique_point_light)
		line_error |= check_point_light_line(&iter);
	else if (ft_strncmp("l ", iter, 2) == 0 && ++count->point_light)
		line_error |= check_point_light_line(&iter);
	else if (ft_strncmp("sp ", iter, 3) == 0 && ++count->sphere)
		line_error |= check_sphere_line(&iter);
	else if (ft_strncmp("pl ", iter, 3) == 0 && ++count->plane)
		line_error |= check_plane_line(&iter);
	else if (ft_strncmp("cy ", iter, 3) == 0 && ++count->cylinder)
		line_error |= check_cylinder_line(&iter);
	else
		line_error |= 1;
	return (line_error);
}
