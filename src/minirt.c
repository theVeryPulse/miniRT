/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:49 by Philip            #+#    #+#             */
/*   Updated: 2024/07/08 00:16:35 by Philip           ###   ########.fr       */
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
	minirt()->eye_canvas_distance = (WIDTH / 2)
		/ tan((new_fov / 2) * 0.01745329251);
}

extern t_minirt	*minirt(void)
{
	static t_minirt	data = (t_minirt){
		.background_color = BLACK
	};
	static bool		first = true;

	if (first)
	{
		first = false;
		update_fov(90);
	}
	return (&data);
}
