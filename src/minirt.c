/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:49 by Philip            #+#    #+#             */
/*   Updated: 2024/07/03 13:40:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "window.h"
#include <math.h>
#include <stdbool.h>

extern t_minirt	*minirt(void)
{
	static t_minirt	data = (t_minirt){
		.fov = 90,
		.background_color = BLACK
	};
	static bool		first = true;

	if (first)
	{
		data.eye_canvas_distance = (WIDTH / 2)
			/ tan((data.fov / 2) * 0.01745329251);
		first = false;
	}
	return (&data);
}
