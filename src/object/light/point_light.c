/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:56:01 by Philip            #+#    #+#             */
/*   Updated: 2024/07/22 19:10:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	point_light(
	t_point position,
	double intensity
)
{
	return ((t_object){
		.type = PointLight,
		.category = Light,
		.intensity = intensity,
		.position = position,
		.direction = (t_vector){0},
		.radius = -1
	});
}
