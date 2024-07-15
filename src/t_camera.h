/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:48:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 19:49:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/vector/t_point.h"

typedef struct s_camera
{
	t_point		position;
	/* Unit direction vector of x-axis */
	t_vector	u;
	/* Unit direction vector of y-axis */
	t_vector	v;
	/* Unit direction vector of z-axis */
	t_vector	w;
}	t_camera;
