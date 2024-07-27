/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/07/27 13:49:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "scene/inc/scene.h"
#include "object/inc/object.h"
#include "window.h"
#include "handle_keypress_event.h"
#include "../lib/minilibx-linux/mlx.h"
#include <X11/X.h> /* DestroyNotify, ButtonReleaseMask */
#include <X11/keysym.h> /* XK_escape */

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "minirt.h"

#include "t_pixel.h"
#include <stddef.h> /* ptrdiff_t */

#include "geometry/inc/geometry.h"

#include <math.h>
#include <unistd.h> /* STDERR */

#include "../lib/libft/inc/libft.h"

#include <stdbool.h>

bool	equals(double a, double b);

int	clean_exit(int exit_status)
{
	t_vars	*vars;

	vars = minirt()->vars;
	printf("exiting...\n");
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	if (vars->scene.objects)
		free(vars->scene.objects);
	if (vars->scene.lights)
		free(vars->scene.lights);
	exit (exit_status);
}

void	set_up_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, handle_keypress_event, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, clean_exit,
		vars);
}

void	set_up_mlx(t_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	vars->img_vars.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	vars->img_vars.addr = mlx_get_data_addr(vars->img_vars.img_ptr,
			&(vars->img_vars.bits_per_pixel), &(vars->img_vars.line_size),
			&(vars->img_vars.endian));
}

/**
 * @brief Puts the image to the window.
 *
 * @param vars Pointer to the variables structure.
 */
void	put_image_to_window_vars(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		vars->img_vars.img_ptr, 0, 0);
}

/**
 * @brief Draws a pixel with the specified color at the given raster space
 *        coordinates on the mlx image.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param pixel The struct with coordinates and color of the pixel to draw.
 */
void	draw_pixel_in_raster_space(t_img_vars *img_vars, t_pixel pixel)
{
	char		*dst;
	ptrdiff_t	offset;

	if (pixel.x >= WIDTH || pixel.x < 0 || pixel.y >= HEIGHT || pixel.y < 0)
	{
		printf("(%d, %d) outside window\n", pixel.x, pixel.y);
		return ;
	}
	offset = pixel.y * img_vars->line_size
		+ pixel.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = pixel.color;
}

void	draw_pixel_in_screen_space(t_img_vars *img_vars, t_pixel pixel)
{
	t_pixel	converted;

	converted = (t_pixel){.x = WIDTH / 2 + pixel.x,
		.y = HEIGHT / 2 - pixel.y, pixel.color};
	draw_pixel_in_raster_space(img_vars, converted);
}

void	test_draw_on_image(t_img_vars *img_vars)
{
	t_pixel	pixel;

	pixel.color = WHITE;
	pixel.y = 0;
	for	(pixel.x = - WIDTH / 2; pixel.x <= WIDTH / 2; ++pixel.x)
		draw_pixel_in_screen_space(img_vars, pixel);
	pixel.x = 0;
	for	(pixel.y = -HEIGHT / 2; pixel.y <= HEIGHT / 2; ++pixel.y)
		draw_pixel_in_screen_space(img_vars, pixel);	
}

double	sign(double n)
{
	if (n >= 0)
		return (1.0);
	else
		return (-1.0);
}

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
void	ray_sphere_intersect(double t[2], t_point ray_origin,
			t_point ray_direction, t_object *sphere, double a)
{
	double		b;
	double		c;
	t_vector	o_minus_c;
	double		discriminant;

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
		double q = -0.5 * (b + sign(b) * sqrt(discriminant));
		t[0] = q / a;
		t[1] = c / q;
	}
}

void	ray_plane_intersect(double *t, t_point ray_origin,
	t_vector ray_direction, t_object *plane, double t_min, double t_max,
	t_object **closest_object, double *closest_t)
{
	double	denominator;

	denominator = vec_dot(plane->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		*t = vec_dot(
			vec_minus(plane->position, ray_origin), plane->direction)
			/ denominator;
		if (*t >= t_min && *t <= t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = plane;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
		}
	}
}

void	ray_disk_intersect(
			double *t,
			t_point ray_origin,
			t_vector ray_direction,
			t_object *disk,
			double t_min,
			double t_max,
			t_object **closest_object,
			double *closest_t)
{
	double		denominator;
	t_vector	intersect;
	t_vector	center_to_intersect;
	double		distance_squared;

	denominator = vec_dot(disk->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		*t = vec_dot(vec_minus(disk->position, ray_origin), disk->direction)
			/ denominator;
		intersect = vec_add(ray_origin, vec_mult(*t, ray_direction));
		center_to_intersect = vec_minus(intersect, disk->position);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= disk->radius_squared
			&& *t >= t_min && *t <= t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = disk;
			if (denominator < 0)
				(*closest_object)->backside = true;
			else
				(*closest_object)->backside = false;
		}
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
		double t[2],
		t_point ray_origin,
		t_vector ray_direction,
		t_object *cylinder,
		double t_min,
		double t_max,
		t_object **closest_object,
		double *closest_t)
{
	t_vector	d_prime;
	t_vector	w_prime;
	t_vector	o_minus_c;

	o_minus_c = vec_minus(ray_origin, cylinder->position);
	d_prime = vec_minus(ray_direction,
		vec_mult(vec_dot(ray_direction, cylinder->direction),
		cylinder->direction));
	w_prime = vec_minus(o_minus_c,
		vec_mult(vec_dot(o_minus_c, cylinder->direction),
		cylinder->direction));

	double	a;
	double	b;
	double	c;

	a = vec_dot(d_prime, d_prime);
	b = 2 * vec_dot(w_prime, d_prime);
	c = vec_dot(w_prime, w_prime) - cylinder->radius_squared;
	
	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		double q = -0.5 * (b + sign(b) * sqrt(discriminant));
		t[0] = q / a;
		t[1] = c / q;
	}

	/* p0​⋅v ≤ (O+td)⋅v ≤ (p0​+hv)⋅v */
	double	proj_min;
	double	proj_max;
	double	proj;
	
	proj_min = vec_dot(cylinder->position, cylinder->direction);
	proj_max = vec_dot(vec_add(cylinder->position,
		vec_mult(cylinder->height, cylinder->direction)), cylinder->direction);
	proj = vec_dot(vec_add(ray_origin, vec_mult(t[0], ray_direction)),
					cylinder->direction);
	if (t[0] >= t_min && t[0] <= t_max && t[0] < *closest_t
		&& proj >= proj_min && proj <= proj_max)
	{
		*closest_t = t[0];
		*closest_object = cylinder;
		cylinder->ray_intersects = CurvedSurface;
	}
	proj = vec_dot(vec_add(ray_origin, vec_mult(t[1], ray_direction)),
					cylinder->direction);
	if (t[1] >= t_min && t[1] <= t_max && t[1] < *closest_t
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
	denominator = vec_dot(cylinder->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		t_point	disk_center = cylinder->position;
		*t = vec_dot(vec_minus(disk_center, ray_origin),
			cylinder->direction) / denominator;
		intersect = vec_add(ray_origin, vec_mult(*t, ray_direction));
		center_to_intersect = vec_minus(intersect, disk_center);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= cylinder->radius_squared
			&& *t >= t_min && *t <= t_max && *t < *closest_t)
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
	denominator = vec_dot(cylinder->direction, ray_direction);
	if (!equals(denominator, 0.0))
	{
		t_point	disk_center;
		disk_center = vec_add(cylinder->position,
			vec_mult(cylinder->height, cylinder->direction));
		*t = vec_dot(vec_minus(disk_center, ray_origin), cylinder->direction)
			/ denominator;
		intersect = vec_add(ray_origin, vec_mult(*t, ray_direction));
		center_to_intersect = vec_minus(intersect, disk_center);
		distance_squared = vec_squared(center_to_intersect);
		if (distance_squared <= cylinder->radius_squared
			&& *t >= t_min && *t <= t_max && *t < *closest_t)
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

/**
 * @brief Checks if a ray hits any object, if hit, record this closest object
 *        and closest_t.
 * 
 * @param scene 
 * @param ray_origin 
 * @param ray_direction 
 * @param t_min 
 * @param t_max 
 * @param closest_object 
 * @param closest_t 
 * @return bool
 */
bool	trace(t_scene *scene,
	t_point ray_origin,
	t_vector ray_direction,
	double t_min,
	double t_max,
	t_object **closest_object, 
	double *closest_t)
{
	double	t[2];
	t_object	*object;
	double	a;

	*closest_object = NULL;
	object = scene->objects;
	a = vec_dot(ray_direction, ray_direction);
	while (object < scene->object_count + scene->objects)
	{
		if (object->type == Sphere)
		{
			ray_sphere_intersect(t, ray_origin, ray_direction,
				object, a);
			if (t[0] >= t_min && t[0] <= t_max && t[0] < *closest_t)
			{
				*closest_t = t[0];
				*closest_object = object;
			}
			if (t[1] >= t_min && t[1] <= t_max && t[1] < *closest_t)
			{
				*closest_t = t[1];
				*closest_object = object;
			}
		}
		else if (object->type == Plane)
		{
			ray_plane_intersect(t, ray_origin, ray_direction, object, t_min,
				t_max, closest_object, closest_t);
		}
		else if (object->type == Disk)
		{
			ray_disk_intersect(t, ray_origin, ray_direction, object, t_min,
				t_max, closest_object, closest_t);
		}
		else if (object->type == Cylinder)
		{
			ray_cylinder_intersect(t, ray_origin, ray_direction, object,
				t_min, t_max, closest_object, closest_t);
		}
		else
		{
		}
		++object;
	}
	return (*closest_object != NULL);
}

/**
 * @brief 
 * 
 * @param normal 
 * @param ray 
 * @return t_vector 
 * @note Equation: R = 2 * dot(N, L) * N - L
 */
static inline t_vector	reflect_ray(t_vector ray, t_vector normal)
{
	return (vec_minus(vec_mult(2 * vec_dot(normal, ray), normal), ray));
}

/**
 * @brief Computes the intensity of reflection at given point, including diffuse
 *        reflection, specular reflection, shade,
 * 
 * @param scene Scene struct, which contains all light sources.
 * @param point Point on object to calculate.
 * @param normal Normal vector at the point on surface.
 * @return double Intensity of the diffuse light at given point, range [0, 1]
 * @note
 * For point light, t_max is 1, this means object on the other side of the light
 * will not cast shadow on current object.
 */
double	compute_lighting(t_scene *scene, t_point point, t_vector normal,
		t_vector view, double specular_exponent)
{
	size_t		i;
	double		intensity;
	t_vector	light;
	double		normal_dot_light;
	double		t_max;

	intensity = 0.0;
	i = 0;
	while (i < scene->light_count)
	{
		if (scene->lights[i].type == AmbientLight)
			intensity += scene->lights[i].intensity;
		else
		{
			if (scene->lights[i].type == PointLight)
			{
				light = vec_minus(scene->lights[i].position, point);
				t_max = vec_len(light);
				light = vec_normalized(light);
			}
			else if (scene->lights[i].type == DirectionalLight)
			{
				light = scene->lights[i].direction;
				t_max = INFINITY;
			}
			else /* Silencing gcc warning */
				t_max = INFINITY;

			/* Shadow check */
			// if (light_is_blocked(scene, point, light, 0.0001, t_max))
			t_object	*closest_object;
			double		closest_t;
			closest_object = NULL;
			closest_t = INFINITY;
			if (trace(scene, point, light, 1e-4, t_max, &closest_object,
				&closest_t))
			{
				++i;
				continue;
			}

			/* Diffuse reflection */
			normal_dot_light = vec_dot(normal, light);
			if (normal_dot_light > 0)
				intensity += scene->lights[i].intensity * normal_dot_light
					/ (vec_len(normal) * vec_len(light));
			
			/* Specular reflection */
			if (specular_exponent > 0.0)
			{
				t_vector	reflection;
				double		reflection_dot_view;

				reflection = reflect_ray(light, normal);
				reflection_dot_view = vec_dot(reflection, view);
				if (reflection_dot_view > 0)
				{
					intensity += scene->lights[i].intensity
						* pow(reflection_dot_view
						/ (vec_len(reflection) * vec_len(view)),
						specular_exponent);
				}
			}
		}
		++i;
	}
	if (intensity >= 1)
		intensity = 1;
	return (intensity);
}

extern t_argb	get_checkerboard_sphere_color(t_point pt, t_argb color1, t_argb color2);

t_argb	cast_ray(t_scene *scene, t_point ray_origin, t_vector ray_direction,
		double t_min, double t_max, uint8_t recursion_depth)
{
	double		closest_t;
	t_object	*closest_object;

	closest_object = NULL;
	closest_t = INFINITY;

	if (!trace(scene, ray_origin, ray_direction, t_min, t_max,
		&closest_object, &closest_t))
		return (minirt()->background_color);

	/* shade(): determining the color of the intersect point */

	t_point		intersection;
	t_vector	unit_normal;
	double		intensity;
	t_argb		local_color;

	intersection = vec_add(ray_origin, vec_mult(closest_t, ray_direction));
	if (closest_object->type == Sphere)
		unit_normal = vec_normalized(
			vec_minus(intersection, closest_object->position));
	else if (closest_object->type == Plane || closest_object->type == Disk)
	{
		unit_normal = closest_object->direction;
		if (closest_object->backside)
			unit_normal = vec_mult(-1.0, unit_normal);
	}
	else if (closest_object->type == Cylinder)
	{
		if (closest_object->ray_intersects == CurvedSurface)
		{
			t_vector q = vec_minus(intersection, closest_object->position);
			t_vector q_on_v = vec_mult(vec_dot(q, closest_object->direction),
				closest_object->direction);
			unit_normal = vec_normalized(vec_minus(q, q_on_v));
		}
		else if (closest_object->ray_intersects == BottomFace
			|| closest_object->ray_intersects == TopFace)
		{
			unit_normal = closest_object->direction;
			if (closest_object->backside)
				unit_normal = vec_mult(-1, unit_normal);
		}
	}
	else
	{
	}
	intensity = compute_lighting(scene, intersection, unit_normal,
		vec_mult(-1, ray_direction), closest_object->specular_exponent);
	if (closest_object->is_checkerboard)
		local_color = color_mult(
			get_checkerboard_sphere_color(
				vec_minus(intersection, closest_object->position),
				WHITE,
				BLACK
			),
			intensity
		);
	else
		local_color = color_mult(closest_object->color, intensity);


	// return (local_color); /* Return color here to skip reflection */

	/* When recursion limit is hit or the other object does not reflect */
	if (recursion_depth <= 0 || closest_object->reflectivity <= 0)
		return (local_color);
	/* Else computes reflected color */
	t_vector	reflection_ray;
	t_argb		reflected_color;

	reflection_ray = reflect_ray(vec_mult(-1, ray_direction), unit_normal);
	reflected_color = cast_ray(scene, intersection, reflection_ray,
		0.001, INFINITY, recursion_depth - 1);
	/* The more smooth the object is, the more light it reflects */
	return (color_add(
		color_mult(local_color, 1- closest_object->reflectivity),
		color_mult(reflected_color, closest_object->reflectivity)));
	/* shade() end */
}

/**
 * @brief 
 * 
 * @param cam 
 * @param pt 
 * @return t_vector 
 * @note
 * dx = (ux)(dx)
 */
t_vector	calculate_ray_direction(t_camera *cam, t_point pt)
{
	t_vector	ray;

	ray.x = cam->u.x * pt.x + cam->v.x * pt.y + cam->w.x * pt.z;
	ray.y = cam->u.y * pt.x + cam->v.y * pt.y + cam->w.y * pt.z;
	ray.z = cam->u.z * pt.x + cam->v.z * pt.y + cam->w.z * pt.z;
	return (ray);
}

/**
 * @brief 
 * @ref computer-graphics-from-scratch / 02-basic-raytracing
 */
void	render_image(t_vars *vars)
{
	t_vector	ray_direction;
	t_pixel		pixel;
	double		t_min;

	pixel.y = HEIGHT / 2;
	while (pixel.y > - HEIGHT / 2)
	{
		pixel.x = - WIDTH / 2;
		while (pixel.x < WIDTH / 2)
		{
			ray_direction = calculate_ray_direction(&(vars->scene.camera),
				(t_point){pixel.x, pixel.y, -(minirt()->eye_canvas_distance)});
			t_min = vec_len(ray_direction);
			vec_normalize(&ray_direction);
			pixel.color = cast_ray(&vars->scene, vars->scene.camera.position,
				ray_direction, t_min, INFINITY, 3);
			draw_pixel_in_screen_space(&vars->img_vars, pixel);
			++pixel.x;
		}
		--pixel.y;
		mlx_string_put(vars->mlx_ptr, vars->win_ptr, HEIGHT - 2 * pixel.y, 5,
			0x009900, "-");
	}
	
}

void	precompute_values(t_scene *scene)
{
	t_object	*object;

	object = scene->objects;
	while (object < scene->objects + scene->object_count)
	{
		if (object->radius > 0)
			object->radius_squared = object->radius * object->radius;
		if (!equals(0.0, vec_len(object->direction)))
			vec_normalize(&object->direction);
		++object;
	}
}

/**
 * @brief 
 * 
 * @param position 
 * @param w z-axis (pointing towards viewer) of the camera
 * @return t_camera 
 */
t_camera	camera(t_raw_point position, t_vector w)
{
	t_camera	camera;

	camera.position = vec_mult(minirt()->unit_one, position);
	if (w.x == 0 && w.z == 0)
	{
		camera.u = (t_vector){1, 0, 0};
		if (w.y > 0) /* Facing down from up */
		{
				camera.v = (t_vector){0, 0, -1},
				camera.w = (t_vector){0, 1, 0};
				return (camera);
		}
		else if (w.y < 0) /* Facing up from down */
		{
				camera.v = (t_vector){0, 0, 1},
				camera.w = (t_vector){0, -1, 0};
				return (camera);
		}
		else /* invalid vector */
		{
			printf("Error: Camera direction cannot be {0, 0, 0}\n");
			clean_exit(1);
		}
	}
	camera.w = vec_normalized(w);
	camera.v = (t_vector){.x = 0, .y = 1, .z = 0};
	camera.u = vec_cross(camera.v, camera.w);
	camera.v = vec_cross(camera.w, camera.u);
	return (camera);
}

void	load_default_scene(t_scene *scene)
{
	scene->camera = camera((t_point){0, 0, 0}, (t_vector){0, 0, 1});
	unsigned int	i = 11;
	allocate_objects(scene, i);
	// scene->objects[--i] = checkerboard_sphere(
	// 	(t_point){10, -150, -2000}, 200.0, 10.0, 0.2);
	scene->objects[--i] = checkerboard_sphere(
		(t_raw_point){0, -0.02, -2}, 0.33, 10.0, 0.2);
	scene->objects[--i] = colored_sphere(
		RED, (t_raw_point){200.0/960.0, 200.0/960.0, -2500.0/960.0},
		300.0/960.0, 5.0, 0.1);
	scene->objects[--i] = colored_sphere(
		YELLOW, (t_raw_point){-700.0/960, -200.0/960.0, -2500.0/960.0},
		300.0/960.0, 1000.0, 0.5);
	// Left wall
	scene->objects[--i] = plane(
		BLUE, (t_raw_point){-960.0/960.0, 0, 0},
		(t_vector){-1, 0, 0}, 100.0, 0.1);
	scene->objects[--i] = plane(
		CYAN, (t_raw_point){960.0/960.0, 0, 0}, (t_vector){1, 0, 0}, 10.0, 0.0);
	// Ceiling
	scene->objects[--i] = plane(
		WHITE, (t_raw_point){0, 540.0/960.0, 0},
		(t_vector){0, 1, 0}, 10.0, 0.0);
	// Floor
	scene->objects[--i] = plane(
		0x808080, (t_raw_point){0, -540.0/960.0, 0},
		(t_vector){0, -1, 0}, 10.0, 0.1);
	// Back wall
	scene->objects[--i] = plane(
		0x808080, (t_raw_point){0, 0, -3000.0/960.0},
		(t_vector){0, 0, -1}, 10.0, 0.0);
	// Disk mirror
	scene->objects[--i] = disk(
		WHITE, (t_raw_point){700.0/960.0, -150.0/960.0, -2500.0/960.0}, 
		(t_vector){1, 0, -1}, 300.0/960.0, 1000.0,
		0.9);
	scene->objects[--i] = cylinder(RED,
		(t_raw_point){10.0/960.0, -540.0/960.0, -2000.0/960.0},
		(t_vector){0, 1, 0}, 500.0/960.0, 200.0/960.0, 1.0, 0.5);

	allocate_lights(scene, 3);
	scene->lights[0] = point_light(
		(t_raw_point){-400.0/960.0, 300.0/960.0, -2900.0/960.0}, 0.5);
	scene->lights[1] = point_light(
		(t_raw_point){400.0/960.0, -300.0/960.0, -1000.0/960.0}, 0.5);
	scene->lights[2] = ambient_light(0.3);
}

void	load_test_scene(t_scene *scene)
{
	scene->camera = camera((t_point){0, 0, 0}, (t_vector){0, 0, 1});

	unsigned int	object_count;
	object_count = 2;
	allocate_objects(scene, object_count);

	// Wall in back
	scene->objects[--object_count] = plane(WHITE, (t_point){0.0/960.0, -100.0/960.0, -2000.0/960.0},
		(t_vector){0, 0, 1}, 10.0, 0.0);
	// scene->objects[--object_count] = checkerboard_sphere(
	// 	(t_raw_point){0.01, 0.02, -2}, 0.5, 100, 0.0);
	scene->objects[--object_count] = cylinder(RED,
		(t_point){10.0/960.0, 10.0/960.0, -1500.0/960.0},
		(t_vector){0, 0, 1}, 200.0/960.0, 200.0/960.0, 1.0, 0.0);
	// scene->objects[--object_count] = disk(RED, (t_point){400.0/960.0, 0, -1500.0/960.0},
	// 	(t_vector){0, 0.1, -1}, 200.0/960.0, 1.0, 0.0);

	unsigned int	light_count;
	light_count = 2;
	allocate_lights(scene, light_count);

	scene->lights[--light_count] = point_light(
		(t_vector){500.0/960.0, 1000.0/960.0, -1000.0/960.0}, 1);
	scene->lights[--light_count] = ambient_light(0.3);
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	t_vars	vars;

	minirt_init(&vars);
	// load_default_scene(&vars.scene);
	load_test_scene(&vars.scene);

	vars.scene.focus = &(vars.scene.objects)[0];
	precompute_values(&vars.scene);

	set_up_mlx(&vars);
	set_up_hooks(&vars);
	render_image(&vars);

	put_image_to_window_vars(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
