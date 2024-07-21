/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/21 20:26:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_object.h"

t_object	disk(
	t_argb color,
	t_point position,
	t_vector direction,
	double radius,
	double specular_exponent,
	double reflectivity
)
{
	return ((t_object){
		.category = Object,
		.type = Disk,
		.radius = radius,
		.color = color,
		.position = position,
		.direction = direction,
		.specular_exponent = specular_exponent,
		.reflectivity = reflectivity,
	});
}
