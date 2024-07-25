/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:27:16 by Philip            #+#    #+#             */
/*   Updated: 2024/07/25 22:28:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

extern t_object	checkerboard_sphere(
					t_raw_point position,
					double radius,
					double specular_exponent,
					double reflectivity);

extern t_object	colored_sphere(
					t_argb color,
					t_raw_point position,
					double radius,
					double specular_exponent,
					double reflectivity);

extern t_object	disk(t_argb color,
					t_raw_point position,
					t_vector direction,
					double radius,
					double specular_exponent,
					double reflectivity);

extern t_object	plane(t_argb color,
					t_raw_point position,
					t_vector direction,
					double specular_exponent,
					double reflectivity);

extern t_object	cylinder(
					t_argb color,
					t_raw_point position,
					t_vector direction,
					double radius,
					double height,
					double specular_exponent,
					double reflectivity);

extern t_object	point_light(t_raw_point position, double intensity);

extern t_object	ambient_light(double intensity);

extern t_object	directional_light(double intensity, t_vector direction);
