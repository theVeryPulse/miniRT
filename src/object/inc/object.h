/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:27:16 by Philip            #+#    #+#             */
/*   Updated: 2024/07/21 20:36:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object	checkerboard_sphere(
				t_point position,
				double radius,
				double specular_exponent,
				double reflectivity);

t_object	colored_sphere(
				t_argb color,
				t_point position,
				double radius,
				double specular_exponent,
				double reflectivity);

t_object	disk(t_argb color,
				t_point position,
				t_vector direction,
				double radius,
				double specular_exponent,
				double reflectivity);

t_object	plane(t_argb color,
				t_point position,
				t_vector direction,
				double specular_exponent,
				double reflectivity);
