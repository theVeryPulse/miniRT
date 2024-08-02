/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:45:59 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:20:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_intersect.h"
#include "../t_closest.h"
#include "../minirt.h"
#include "../ray/t_ray.h"
#include "../geometry/inc/geometry.h"
#include "../object/inc/object.h"
#include "../maths/inc/maths.h"
#include "t_triplet.h"
#include <math.h>

extern void	ray_cylinder_intersect(
				t_ray *ray,
				t_object *c,
				t_closest *closest);

static void	calculate_abc(t_triplet *d3, t_ray *ray, t_object *c);
static void	ray_curved_surface_intersect(double t[2], t_triplet *d3);
static void	update_solution_if_t_in_cylinder_height(
				t_ray *ray,
				t_object *c,
				t_closest *closest,
				double t[2]);

/**
 * @brief 
 * 
 * @ref
 * https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20
 * raytracing%20shapes.htm
 */
extern void	ray_cylinder_intersect(
		t_ray *ray,
		t_object *c,
		t_closest *closest)
{
	double		t[2];
	t_triplet	d3;
	t_object	top_face;

	calculate_abc(&d3, ray, c);
	ray_curved_surface_intersect(t, &d3);
	update_solution_if_t_in_cylinder_height(ray, c, closest, t);
	top_face = disk((t_d){c->color, vec_div(vec_add(c->position,
					vec_mult(c->height, c->direction)), minirt()->unit_one),
			c->direction, c->radius / minirt()->unit_one,
			c->specular_exponent, c->reflectivity});
	if (ray_disk_intersect(ray, c, closest))
	{
		c->ray_intersects = BottomFace;
		closest->object = c;
	}
	if (ray_disk_intersect(ray, &top_face, closest))
	{
		c->ray_intersects = TopFace;
		closest->object = c;
		c->backside = top_face.backside;
	}
}

static void	calculate_abc(t_triplet *d3, t_ray *ray, t_object *c)
{
	t_vector	d_prime;
	t_vector	w_prime;
	t_vector	o_minus_c;

	o_minus_c = vec_minus(ray->origin, c->position);
	d_prime = vec_minus(ray->direction,
			vec_mult(vec_dot(ray->direction, c->direction), c->direction));
	w_prime = vec_minus(o_minus_c,
			vec_mult(vec_dot(o_minus_c, c->direction), c->direction));
	d3->a = vec_dot(d_prime, d_prime);
	d3->b = 2 * vec_dot(w_prime, d_prime);
	d3->c = vec_dot(w_prime, w_prime) - c->radius_squared;
}

static void	ray_curved_surface_intersect(double t[2], t_triplet *d3)
{
	double	discriminant;
	double	q;

	discriminant = d3->b * d3->b - 4 * d3->a * d3->c;
	if (discriminant < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		q = -0.5 * (d3->b + sign(d3->b) * sqrt(discriminant));
		t[0] = q / d3->a;
		t[1] = d3->c / q;
	}
}

/**
 * @brief 
 * 
 * @param ray 
 * @param cylinder 
 * @param closest_object 
 * @param closest_t 
 * @param t 
 * @note
 * p0​⋅v ≤ (O+td)⋅v ≤ (p0​+hv)⋅v
 */
static void	update_solution_if_t_in_cylinder_height(
			t_ray *ray,
			t_object *c,
			t_closest *closest,
			double t[2])
{
	double	proj_min;
	double	proj_max;
	double	proj;

	proj_min = vec_dot(c->position, c->direction);
	proj_max = vec_dot(vec_add(c->position,
				vec_mult(c->height, c->direction)), c->direction);
	proj = vec_dot(vec_add(ray->origin, vec_mult(t[0], ray->direction)),
			c->direction);
	if (t[0] >= ray->t_min && t[0] <= ray->t_max && t[0] < closest->t
		&& proj >= proj_min && proj <= proj_max)
	{
		closest->t = t[0];
		closest->object = c;
		c->ray_intersects = CurvedSurface;
	}
	proj = vec_dot(vec_add(ray->origin, vec_mult(t[1], ray->direction)),
			c->direction);
	if (t[1] >= ray->t_min && t[1] <= ray->t_max && t[1] < closest->t
		&& proj >= proj_min && proj <= proj_max)
	{
		closest->t = t[1];
		closest->object = c;
		c->ray_intersects = CurvedSurface;
	}
}
