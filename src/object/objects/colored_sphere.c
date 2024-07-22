/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/07/22 20:12:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	colored_sphere(
	t_argb color,
	t_point position,
	double radius,
	double specular_exponent,
	double reflectivity
)
{
	return ((t_object){
		.type = Sphere,
		.category = Object,
		.color = color,
		.position = position,
		.radius = radius,
		.specular_exponent = specular_exponent,
		.reflectivity = reflectivity,
		.is_checkerboard = false
	});
}
