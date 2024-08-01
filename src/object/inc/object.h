/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:27:16 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 21:41:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../t_object.h"

typedef struct s_cs
{
	t_raw_point	position;
	double		radius;
	double		specular_exponent;
	double		reflectivity;
}	t_cs;

extern t_object	checkerboard_sphere(t_cs cs);

typedef struct s_s
{
	t_argb		color;
	t_raw_point	position;
	double		radius;
	double		specular_exponent;
	double		reflectivity;
}	t_s;

extern t_object	colored_sphere(t_s s);

typedef struct s_d
{
	t_argb		color;
	t_raw_point	position;
	t_vector	direction;
	double		radius;
	double		specular_exponent;
	double		reflectivity;
}	t_d;

extern t_object	disk(t_d d);

typedef struct s_p
{
	t_argb		color;
	t_raw_point	position;
	t_vector	direction;
	double		specular_exponent;
	double		reflectivity;
}	t_p;

extern t_object	plane(t_p p);

typedef struct s_c
{
	t_argb		color;
	t_raw_point	position;
	t_vector	direction;
	double		radius;
	double		height;
	double		specular_exponent;
	double		reflectivity;
}	t_c;

extern t_object	cylinder(t_c c);

extern t_object	point_light(t_raw_point position, double intensity);

extern t_object	ambient_light(double intensity);

extern t_object	directional_light(double intensity, t_vector direction);

#endif // OBJECT_H