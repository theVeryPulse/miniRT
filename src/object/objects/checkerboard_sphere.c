/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:25:40 by Philip            #+#    #+#             */
/*   Updated: 2024/07/22 19:23:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	checkerboard_sphere(
	t_point position,
	double radius,
	double specular_exponent,
	double reflectivity
)
{
	return ((t_object){
		.category = Object,
		.type = Sphere,
		.position = position,
		.radius = radius,
		.specular_exponent = specular_exponent,
		.reflectivity = reflectivity,
		.is_checkerboard = true
	});
}
