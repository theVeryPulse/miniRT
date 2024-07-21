/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/07/21 13:20:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include "t_vars.h"
#include "window.h"
#include "handle_keypress_event.h"
#include <X11/X.h> /* DestroyNotify, ButtonReleaseMask */
#include <X11/keysym.h> /* XK_escape */

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "minirt.h"

#include "t_pixel.h"
#include <stddef.h> /* ptrdiff_t */

#include "geometry/inc/geometry.h"
#include "t_scene.h"

#include <math.h>
#include <unistd.h> /* STDERR */

#include "../lib/libft/inc/libft.h"

#include <stdbool.h>

void	render_image(t_vars *vars);
void	put_image_to_window_vars(t_vars *vars);
void	ray_sphere_intersect(double t[2], t_point ray_origin,
			t_point ray_direction, t_object *sphere, double a);

int	destroy_exit(t_vars *vars)
{
	printf("exiting...\n");
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	if (vars->scene.objects)
		free(vars->scene.objects);
	if (vars->scene.lights)
		free(vars->scene.lights);
	exit (0);
}

void	set_up_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, handle_keypress_event, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit,
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

bool	light_is_blocked(t_scene *scene, t_point shadow_ray_origin,
	t_vector shadow_ray_direction, double t_min, double t_max)
{
	double		t[2];
	size_t		i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == Sphere)
		{
			ray_sphere_intersect(t, shadow_ray_origin, shadow_ray_direction,
				&(scene->objects)[i],
				vec_dot(shadow_ray_direction, shadow_ray_direction));
			if (t[0] >= t_min && t[0] <= t_max)
				return (true);
		}
		else if (scene->objects[i].type != Sphere)
		{
		}
		++i;
	}
	return (false);
}

void	ray_plane_intersect(double *t, t_point ray_origin,
	t_vector ray_direction, t_object *plane, double t_min, double t_max,
	t_object **closest_object, double *closest_t)
{
	double	denominator;

	denominator = vec_dot(plane->direction, ray_direction);
	if (denominator > 1e-6)
	{
		*t = vec_dot(
			vec_minus(plane->position, ray_origin), plane->direction)
			/ denominator;
		if (*t >= t_min && *t <= t_max && *t < *closest_t)
		{
			*closest_t = *t;
			*closest_object = plane;
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

	*closest_object = NULL;
	object = scene->objects;
	while (object < scene->object_count + scene->objects)
	{
		if (object->type == Sphere)
		{
			ray_sphere_intersect(t, ray_origin, ray_direction,
				object, vec_dot(ray_direction, ray_direction));
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
			if (specular_exponent != -1)
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

extern t_argb	checkerboard_color_sphere(t_point pt, t_argb color1, t_argb color2);

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
	else if (closest_object->type == Plane)
		unit_normal = closest_object->direction;
	else
	{
	}
	intensity = compute_lighting(scene, intersection, unit_normal,
		vec_mult(-1, ray_direction), closest_object->specular_exponent);
	if (closest_object->is_checkerboard)
		local_color = color_mult(
			checkerboard_color_sphere(
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

void	allocate_objects(t_scene *scene, unsigned int object_count)
{
	scene->objects = (t_object *)ft_calloc(object_count, sizeof(t_object));
	scene->object_count = object_count;
}

void	allocate_lights(t_scene *scene, unsigned int light_count)
{
	scene->lights = (t_object *)ft_calloc(light_count, sizeof(t_object));
	scene->light_count = light_count;
}

void	calculate_radius_squared(t_scene *scene)
{
	t_object	*object;

	object = scene->objects;
	while (object < scene->objects + scene->object_count)
	{
		if (object->type == Sphere)
			object->radius_squared = object->radius * object->radius;
		++object;
	}
}

void	precompute_values(t_scene *scene)
{
	t_object	*object;

	object = scene->objects;
	while (object < scene->objects + scene->object_count)
	{
		if (object->type == Sphere || object->type == Disk)
			object->radius_squared = object->radius * object->radius;
		else if (object->type == Plane
			|| object->type == DirectionalLight
			|| object->type == Disk)
			vec_normalize(&object->direction);
		++object;
	}
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	t_vars	vars;

	set_up_mlx(&vars);
	set_up_hooks(&vars);
	minirt_init();

	vars.scene.camera = (t_camera){
		.position = (t_point){0, 0, 0},
		.u = (t_vector){1.0, 0.0, 0.0},
		.v = (t_vector){0.0, 1.0, 0.0},
		.w = (t_vector){0.0, 0.0, 1.0}
		// Turn 30 degrees left
		/* .u = (t_vector){sqrt(3) / 2, 0, -0.5},
		.v = (t_vector){0, 1, 0},
		.w = (t_vector){0.5, 0, sqrt(3) / 2} */
	};

	allocate_objects(&vars.scene, 7);
	vars.scene.objects[0] = (t_object){
		.type = Sphere,
		.category = Object,
		.color = MAGENTA,
		.position = (t_point){0, 0, -3000},
		.radius = 500.0,
		.specular_exponent = 10, /* Shiny */
		.reflectivity = 0.2, /* A bit reflective */
		.is_checkerboard = true
	};
	vars.scene.objects[1] = (t_object){
		.type = Sphere,
		.category = Object,
		.color = CYAN,
		.position = (t_point){1000, 1000, -5000},
		.radius = 1800.0,
		.specular_exponent = 100, /* Somewhat shiny */
		.reflectivity = 0.3, /* A bit more reflective */
		.is_checkerboard = false
	};
	vars.scene.objects[2] = (t_object){
		.type = Sphere,
		.category = Object,
		.color = YELLOW,
		.position = (t_point){-1000, -300, -2500},
		.radius = 300.0,
		.specular_exponent = 1000, /* Very shiny */
		.reflectivity = 0.5, /* Half reflective */
		.is_checkerboard = false
	};
	vars.scene.objects[3] = (t_object){
		.category = Object,
		.type = Plane,
		.color = BLUE,
		.position = (t_point){-960, 0, 0},
		.direction = (t_point){-1, 0, 0},
		.specular_exponent = 100,
		.reflectivity = 0.1,
		.is_checkerboard = false
	};
	vars.scene.objects[4] = (t_object){
		.category = Object,
		.type = Plane,
		.color = CYAN,
		.position = (t_point){960, 0, 0},
		.direction = (t_point){1, 0, 0},
		.specular_exponent = 10,
		.reflectivity = 0.1,
		.is_checkerboard = false
	};
	vars.scene.objects[5] = (t_object){
		.category = Object,
		.type = Plane,
		.color = WHITE,
		.position = (t_point){0, 540, 0},
		.direction = (t_point){0, 1, 0},
		.specular_exponent = 10,
		.reflectivity = 0.0,
		.is_checkerboard = false
	};
	vars.scene.objects[6] = (t_object){
		.category = Object,
		.type = Plane,
		.color = 0x808080,
		.position = (t_point){0, -540, 0},
		.direction = (t_point){0, -1, 0},
		.specular_exponent = 10,
		.reflectivity = 0.0,
		.is_checkerboard = false
	};
	// calculate_radius_squared(&vars.scene);

	allocate_lights(&vars.scene, 3);
	vars.scene.lights[0] = (t_object){
		.type = PointLight,
		.category = Light,
		.intensity = 0.5,
		.position = (t_point){-400, 300, -3000},
		.direction = (t_vector){0},
		.radius = -1
	};
#if 0
	vars.scene.lights[1] = (t_object){
		.type = DirectionalLight,
		.category = Light,
		.intensity = 0.0,
		.direction = (t_vector){0, 0, 0.1}
		};
#else // Two point lights for better shadow effect
	vars.scene.lights[1] = (t_object){
		.type = PointLight,
		.category = Light,
		.intensity = 0.5,
		.position = (t_point){400, -300, -1500},
		.direction = (t_vector){0},
		.radius = -1
	};
#endif
	vars.scene.lights[2] = (t_object){
		.type = AmbientLight,
		.category = Light,
		.intensity = 0.05,
		.radius = -1
	};

	// allocate_objects(&vars.scene, 2);
	// vars.scene.objects[0] = (t_object){
	// 	.category = Object,
	// 	.type = Sphere,
	// 	.color = CYAN,
	// 	.position = (t_point){600, 0, -2000},
	// 	.radius = 500,
	// 	.direction = (t_point){-1, 0, -1},
	// 	.specular_exponent = 1000, /* Somewhat shiny */
	// 	.reflectivity = 0.8, /* A bit more reflective */
	// 	.is_checkerboard = true
	// };
	// vars.scene.objects[1] = (t_object){
	// 	.category = Object,
	// 	.type = Sphere,
	// 	.color = CYAN,
	// 	.position = (t_point){-600, 0, -2000},
	// 	.radius = 500,
	// 	.direction = (t_point){-1, 0, -1},
	// 	.specular_exponent = 100, /* Somewhat shiny */
	// 	.reflectivity = 0.1, /* A bit more reflective */
	// 	.is_checkerboard = true
	// };
	// calculate_radius_squared(&vars.scene);

	vars.scene.focus = &(vars.scene.objects)[0];
	precompute_values(&vars.scene);
	render_image(&vars);

	put_image_to_window_vars(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
