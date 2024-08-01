/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:49 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 15:38:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "window.h"
#include <math.h>
#include <stdbool.h>

extern void	update_fov(double new_fov)
{
	if (new_fov <= 0 || new_fov >= 180)
		return ;
	minirt()->fov = new_fov;
	minirt()->eye_canvas_distance = (WIDTH / 2) / tan((new_fov / 2)
		* DEG_TO_RAD);
	minirt()->scale = tan(minirt()->fov * 0.5 * DEG_TO_RAD);
}

extern t_minirt	*minirt(void)
{
	static t_minirt	data;

	return (&data);
}
