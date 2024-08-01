/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:45:59 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 18:43:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ray/t_ray.h"
#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"
#include "t_triplet.h"
#include <math.h>

static void	calculate_abc(t_triplet *d3, t_ray *ray, t_object *cylinder)
{
	t_vector	d_prime;
	t_vector	w_prime;
	t_vector	o_minus_c;

	o_minus_c = vec_minus(ray->origin, cylinder->position);
	d_prime = vec_minus(ray->direction,
		vec_mult(vec_dot(ray->direction, cylinder->direction),
		cylinder->direction));
	w_prime = vec_minus(o_minus_c,
		vec_mult(vec_dot(o_minus_c, cylinder->direction),
		cylinder->direction));

	d3->a = vec_dot(d_prime, d_prime);
	d3->b = 2 * vec_dot(w_prime, d_prime);
	d3->c = vec_dot(w_prime, w_prime) - cylinder->radius_squared;
}

static void	calculate_t1t2_on_curved_surface(double t[2], t_triplet *d3)
{
	double	discriminant;

	discriminant = d3->b * d3->b - 4 * d3->a * d3->c;
	if (discriminant < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		double q = -0.5 * (d3->b + sign(d3->b) * sqrt(discriminant));
		t[0] = q / d3->a;
		t[1] = d3->c / q;
	}
}

/**
 * @brief 
 * 
 * @ref
 * https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20
 * raytracing%20shapes.htm
 */
void	ray_cylinder_intersect(
		t_ray *ray,
		t_object *cylinder,
		t_object **closest_object,
		double *closest_t)
{
	double		t[2];
	t_triplet	d3;

	calculate_abc(&d3, ray, cylinder);
	calculate_t1t2_on_curved_surface(t, &d3);

	/* p0​⋅v ≤ (O+td)⋅v ≤ (p0​+hv)⋅v */
	double	proj_min;
	double	proj_max;
	double	proj;
	
	proj_min = vec_dot(cylinder->position, cylinder->direction);
	proj_max = vec_dot(vec_add(cylinder->position,
		vec_mult(cylinder->height, cylinder->direction)), cylinder->direction);
	proj = vec_dot(vec_add(ray->origin, vec_mult(t[0], ray->direction)),
					cylinder->direction);
	if (t[0] >= ray->t_min && t[0] <= ray->t_max && t[0] < *closest_t
		&& proj >= proj_min && proj <= proj_max)
	{
		*closest_t = t[0];
		*closest_object = cylinder;
		cylinder->ray_intersects = CurvedSurface;
	}
	proj = vec_dot(vec_add(ray->origin, vec_mult(t[1], ray->direction)),
					cylinder->direction);
	if (t[1] >= ray->t_min && t[1] <= ray->t_max && t[1] < *closest_t
		&& proj >= proj_min && proj <= proj_max)
	{
		*closest_t = t[1];
		*closest_object = cylinder;
		cylinder->ray_intersects = CurvedSurface;
	}

	/* Caps */
	double		denominator;
	t_vector	intersect;
	t_vector	center_to_intersect;
	double		distance_squared;
	
	/* Bottom cap */
	denominator = vec_dot(cylinder->direction, ray->direction);
	if (!equals(denominator, 0.0))
	{
		t_point	disk_center = cylinder->position;
		*t = vec_dot(vec_minus(disk_center, ray->origin),
			cylinder->direction) / denominator;
		intersect = vec_add(ray->origin, vec_mult(*t, ray->direction));
		center_to_intersect = vec_minus(intersect, disk_center);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= cylinder->radius_squared
			&& *t >= ray->t_min && *t <= ray->t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = cylinder;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
			cylinder->ray_intersects = BottomFace;
		}
	}

	/* Top cap */
	denominator = vec_dot(cylinder->direction, ray->direction);
	if (!equals(denominator, 0.0))
	{
		t_point	disk_center;
		disk_center = vec_add(cylinder->position,
			vec_mult(cylinder->height, cylinder->direction));
		*t = vec_dot(vec_minus(disk_center, ray->origin), cylinder->direction)
			/ denominator;
		intersect = vec_add(ray->origin, vec_mult(*t, ray->direction));
		center_to_intersect = vec_minus(intersect, disk_center);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= cylinder->radius_squared
			&& *t >= ray->t_min && *t <= ray->t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = cylinder;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
			cylinder->ray_intersects = TopFace;
		}
	}
}
