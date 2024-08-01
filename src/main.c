/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 23:44:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "load_file/inc/load_file.h"
#include "scene/inc/scene.h"
#include "object/inc/object.h"
#include "tracer/inc/trace.h"
#include "ray/t_ray.h"
#include "t_closest.h"
#include "window.h"
#include "key_press/inc/key_press.h"
#include "maths/inc/maths.h"
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

#define RED_ERROR "\033[91merror: \033[0m"

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
			t_ray		shadow_ray;
			t_closest	closest;
			
			closest.object = NULL;
			closest.t = INFINITY;
			shadow_ray.origin = point;
			shadow_ray.direction = light;
			shadow_ray.t_min = 1e-4;
			shadow_ray.t_max = t_max;
			if (trace(scene, &shadow_ray, &closest))
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

t_argb	cast_ray(t_scene *scene, t_ray *ray, uint8_t recursion_depth);

t_argb	shade(t_scene *scene, t_ray *ray, t_closest *closest,
			uint8_t recursion_depth)
{
	t_point		intersection;
	t_vector	unit_normal;
	double		intensity;
	t_argb		local_color;

	intersection = vec_add(ray->origin, vec_mult(closest->t, ray->direction));
	if (closest->object->type == Sphere)
		unit_normal = vec_normalized(
			vec_minus(intersection, closest->object->position));
	else if (closest->object->type == Plane || closest->object->type == Disk)
	{
		unit_normal = closest->object->direction;
		if (closest->object->backside)
			unit_normal = vec_mult(-1.0, unit_normal);
	}
	else if (closest->object->type == Cylinder)
	{
		if (closest->object->ray_intersects == CurvedSurface)
		{
			t_vector q = vec_minus(intersection, closest->object->position);
			t_vector q_on_v = vec_mult(vec_dot(q, closest->object->direction),
				closest->object->direction);
			unit_normal = vec_normalized(vec_minus(q, q_on_v));
		}
		else if (closest->object->ray_intersects == BottomFace
			|| closest->object->ray_intersects == TopFace)
		{
			unit_normal = closest->object->direction;
			if (closest->object->backside)
				unit_normal = vec_mult(-1, unit_normal);
		}
	}
	else
	{
	}
	intensity = compute_lighting(scene, intersection, unit_normal,
		vec_mult(-1, ray->direction), closest->object->specular_exponent);
	if (closest->object->is_checkerboard)
		local_color = color_mult(
			get_checkerboard_sphere_color(
				vec_minus(intersection, closest->object->position),
				WHITE,
				BLACK
			),
			intensity
		);
	else
		local_color = color_mult(closest->object->color, intensity);

	// return (local_color); /* Return color here to skip reflection */

	/* When recursion limit is hit or the other object does not reflect */
	if (recursion_depth <= 0 || closest->object->reflectivity <= 0)
		return (local_color);
	/* Else computes reflected color */
	t_ray	reflection_ray;
	t_argb	reflected_color;

	reflection_ray.origin = intersection;
	reflection_ray.direction = reflect_ray(
		vec_mult(-1, ray->direction), unit_normal);
	reflection_ray.t_min = 0.001;
	reflection_ray.t_max = INFINITY;
	reflected_color = cast_ray(scene, &reflection_ray, recursion_depth - 1);
	/* The more smooth the object is, the more light it reflects */
	return (color_add(
		color_mult(local_color, 1 - closest->object->reflectivity),
		color_mult(reflected_color, closest->object->reflectivity)));
}

t_argb	cast_ray(t_scene *scene, t_ray *ray, uint8_t recursion_depth)
{
	t_closest	closest;

	closest.object = NULL;
	closest.t = INFINITY;
	if (!trace(scene, ray, &closest))
		return (minirt()->background_color);
	else
		return (shade(scene, ray, &closest, recursion_depth));
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
	t_ray		ray;
	t_pixel		pixel;

	pixel.y = HEIGHT / 2;
	while (pixel.y > - HEIGHT / 2)
	{
		pixel.x = - WIDTH / 2;
		while (pixel.x < WIDTH / 2)
		{
			ray.origin = vars->scene.camera.position;
			ray.direction = calculate_ray_direction(&(vars->scene.camera),
				(t_point){pixel.x, pixel.y, -(minirt()->eye_canvas_distance)});
			ray.t_min = vec_len(ray.direction);
			ray.t_max = INFINITY;
			vec_normalize(&ray.direction);
			pixel.color = cast_ray(&vars->scene, &ray, 3);
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
	t_object	*o;

	o = scene->objects;
	while (o < scene->objects + scene->object_count)
	{
		if (o->direction.x != 0 || o->direction.y != 0 || o->direction.z != 0)
			vec_normalize(&o->direction);
		++o;
	}
	minirt()->eye_canvas_distance = minirt()->eye_canvas_distance = (WIDTH / 2)
		/ tan((minirt()->fov / 2) * DEG_TO_RAD);
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

	camera = (t_camera){0};
	camera.position = vec_mult(minirt()->unit_one, position);
	if (w.x == 0 && w.z == 0 && w.y > 0)
	{
		camera.u = (t_vector){1, 0, 0};
		camera.v = (t_vector){0, 0, -1},
		camera.w = (t_vector){0, 1, 0};
		return (camera);
	}
	else if (w.x == 0 && w.z == 0 && w.y < 0)
	{
		camera.u = (t_vector){1, 0, 0};
		camera.v = (t_vector){0, 0, 1},
		camera.w = (t_vector){0, -1, 0};
		return (camera);
	}
	camera.w = vec_normalized(w);
	camera.v = (t_vector){0, 1, 0};
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
	// scene->objects[--i] = checkerboard_sphere(
	// 	(t_raw_point){0, -0.02, -2}, 0.33, 10.0, 0.2);

	scene->objects[--i] = checkerboard_sphere(
		(t_cs){(t_raw_point){0, -0.02, -2}, 0.33, 10.0, 0.2});
		
	scene->objects[--i] = colored_sphere((t_s){
		RED, (t_raw_point){200.0/960.0, 200.0/960.0, -2500.0/960.0},
		300.0/960.0, 5.0, 0.1});

	scene->objects[--i] = colored_sphere((t_s){
		RED, (t_raw_point){200.0/960.0, 200.0/960.0, -2500.0/960.0},
		300.0/960.0, 5.0, 0.1});
	
	scene->objects[--i] = colored_sphere((t_s){
		YELLOW, (t_raw_point){-700.0/960, -200.0/960.0, -2500.0/960.0},
		300.0/960.0, 1000.0, 0.5});
	// Left wall
	scene->objects[--i] = plane((t_p){
		BLUE, (t_raw_point){-960.0/960.0, 0, 0},
		(t_vector){-1, 0, 0}, 100.0, 0.1});
	scene->objects[--i] = plane((t_p){
		CYAN, (t_raw_point){960.0/960.0, 0, 0}, (t_vector){1, 0, 0}, 10.0, 0.0});
	// Ceiling
	scene->objects[--i] = plane((t_p){
		WHITE, (t_raw_point){0, 540.0/960.0, 0},
		(t_vector){0, 1, 0}, 10.0, 0.0});
	// Floor
	scene->objects[--i] = plane((t_p){
		0x808080, (t_raw_point){0, -540.0/960.0, 0},
		(t_vector){0, -1, 0}, 10.0, 0.1});
	// Back wall
	scene->objects[--i] = plane((t_p){
		0x808080, (t_raw_point){0, 0, -3000.0/960.0},
		(t_vector){0, 0, -1}, 10.0, 0.0});
	// Disk mirror
	scene->objects[--i] = disk((t_d){
		WHITE, (t_raw_point){700.0/960.0, -150.0/960.0, -2500.0/960.0}, 
		(t_vector){1, 0, -1}, 300.0/960.0, 1000.0,
		0.9});
	scene->objects[--i] = cylinder((t_c){RED,
		(t_raw_point){10.0/960.0, -540.0/960.0, -2000.0/960.0},
		(t_vector){0, 1, 0}, 500.0/960.0, 200.0/960.0, 1.0, 0.5});

	allocate_lights(scene, 3);
	scene->lights[0] = point_light(
		(t_raw_point){-400.0/960.0, 300.0/960.0, -2900.0/960.0}, 0.5);
	scene->lights[1] = point_light(
		(t_raw_point){400.0/960.0, -300.0/960.0, -1000.0/960.0}, 0.5);
	scene->lights[2] = ambient_light(0.3);

	scene->focus = scene->objects;
}

void	load_test_scene(t_scene *scene)
{
	scene->camera = camera((t_point){0, 0, 0}, (t_vector){0, 0, 1});

	unsigned int	object_count;
	object_count = 2;
	allocate_objects(scene, object_count);

	// Wall in back
	scene->objects[--object_count] = plane((t_p){WHITE, (t_point){0.0/960.0, -100.0/960.0, -2000.0/960.0},
		(t_vector){0, 0, 1}, 10.0, 0.0});
	// scene->objects[--object_count] = checkerboard_sphere(
	// 	(t_raw_point){0.01, 0.02, -2}, 0.5, 100, 0.0);
	scene->objects[--object_count] = cylinder((t_c){RED,
		(t_point){10.0/960.0, 10.0/960.0, -1500.0/960.0},
		(t_vector){0, 0, 1}, 200.0/960.0, 200.0/960.0, 1.0, 0.0});
	// scene->objects[--object_count] = disk(RED, (t_point){400.0/960.0, 0, -1500.0/960.0},
	// 	(t_vector){0, 0.1, -1}, 200.0/960.0, 1.0, 0.0);

	unsigned int	light_count;
	light_count = 2;
	allocate_lights(scene, light_count);

	scene->lights[--light_count] = point_light(
		(t_vector){500.0/960.0, 1000.0/960.0, -1000.0/960.0}, 1);
	scene->lights[--light_count] = ambient_light(0.3);
}

void	check_argc(int argc)
{
	if (argc == 1)
		exit(0);
	else if (argc > 2)
	{
		printf(RED_ERROR"there should only be 1 argument.\n");
		exit(1);
	}
}

void	check_filename(const char *filename)
{
	if (ft_strlen(filename) <= 3)
	{
		printf(RED_ERROR"invalid filename: \"%s\"\n", filename);
		exit(1);
	}
	if (!ft_strchr(filename, '.'))
	{
		printf(RED_ERROR"unrecognised file format.\n");
		exit(1);
	}
	else if (ft_strncmp(".rt", ft_strrchr(filename, '.'), 4))
	{
		printf(RED_ERROR"unrecognised file format: \"%s\"\n",
			ft_strrchr(filename, '.'));
		exit(1);
	}
}

int	main(int argc, char const *argv[])
// int	main(void)
{
	t_vars	vars;

	check_argc(argc);
	check_filename(argv[1]);
	

	minirt_init(&vars);
	load_default_scene(&vars.scene);
	// load_test_scene(&vars.scene);
	// load_scene_from_file(&vars.scene, argv[1]);

	precompute_values(&vars.scene);

	set_up_mlx(&vars);
	set_up_hooks(&vars);
	render_image(&vars);

	put_image_to_window_vars(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
