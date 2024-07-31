/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:48:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 18:18:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
# define T_CAMERA_H

#include "geometry/vector/t_point.h"
#include <stdbool.h>

typedef struct s_camera
{
	t_point		position;
	/* Unit direction vector of x-axis */
	t_vector	u;
	/* Unit direction vector of y-axis */
	t_vector	v;
	/* Unit direction vector of z-axis */
	t_vector	w;
	bool		error;
}	t_camera;

#endif /* T_CAMERA_H */