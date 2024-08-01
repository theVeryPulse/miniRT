/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:57:33 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:09:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"
#include <math.h>

static void	update_solution(
				double t[2],
				t_object *sphere,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

/**
 * @brief 
 * 
 * @param t 
 * @param ray_origin 
 * @param point_on_canvas 
 * @param sphere 
 * @note
 * |O+tD-C|^2 - R^2 = 0
 *  O: ray origin
 *  D: ray direction, whether normalized or not will affect the range of
 *     solution of 't'
 *  C: sphere center
 *  R: sphere radius
 * => in the form of: ax^2 + bx + c
 * => a = D^2; b = 2D(O-C); c=|O-C|^2-R^2
 * 
 * a = vec_dot(ray_direction, ray_direction)
 * 'a' remains unchanged for the same ray.
 * 
 * => t1 = (-b - sqrt(b^2 - 4ac)) / 2a
 * => t2 = (-b + sqrt(b^2 - 4ac)) / 2a
 * 
 * "However, due to the finite precision with which real numbers are represented 
 * on computers, this formula can suffer from a loss of significance." A more
 * stable equation is used instead.
 * 
 * q = -0.5 * (b + sign(b) * sqrt(b^2 - 4ac))
 * => t1 = q / a
 * => t2 = c / q
 * 
 * @ref 
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/
 * minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
 */
void	ray_sphere_intersect(
			double t[2],
			t_point ray_origin,
			t_point ray_direction,
			t_object *sphere,
			double a,
			double t_min,
			double t_max,
			t_object **closest_object,
			double *closest_t)
{
	double		b;
	double		c;
	t_vector	o_minus_c;
	double		discriminant;
	double		q;

	o_minus_c = vec_minus(ray_origin, sphere->position);
	b = 2 * vec_dot(o_minus_c, ray_direction);
	c = vec_dot(o_minus_c, o_minus_c) - sphere->radius_squared;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		q = -0.5 * (b + sign(b) * sqrt(discriminant));
		t[0] = q / a;
		t[1] = c / q;
	}
	update_solution(t, sphere, t_min, t_max, closest_object, closest_t);
}

static void	update_solution(
			double t[2],
			t_object *sphere,
			double t_min,
			double t_max,
			t_object **closest_object,
			double *closest_t)
{
	if (t[0] >= t_min && t[0] <= t_max && t[0] < *closest_t)
	{
		*closest_t = t[0];
		*closest_object = sphere;
	}
	if (t[1] >= t_min && t[1] <= t_max && t[1] < *closest_t)
	{
		*closest_t = t[1];
		*closest_object = sphere;
	}
}
