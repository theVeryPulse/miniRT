/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/07/03 11:36:49 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include "vars.h"
#include "window.h"
#include <X11/X.h> /* DestroyNotify, ButtonReleaseMask */
#include <X11/keysym.h> /* XK_escape */

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "minirt.h"

#include "t_pixel.h"
#include <stddef.h> /* ptrdiff_t */

#include "t_point.h"
#include "t_scene.h"

#include <math.h>

#include "../lib/libft/inc/libft.h"

void	basic_raytracing(t_img_vars *img_vars, t_scene *scene);
void	put_image_to_window_vars(t_vars *vars);

int	destroy_exit(t_vars *vars)
{
	printf("exiting...\n");
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	if (vars->scene.objects)
		free(vars->scene.objects);
	exit (0);
}

int	handle_key(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
	else if (key == XK_Tab)
	{
		++(vars->scene.focus);
		if (vars->scene.focus == vars->scene.objects + vars->scene.object_count)
			vars->scene.focus = vars->scene.lights;
		else if (vars->scene.focus == vars->scene.lights + vars->scene.light_count)
			vars->scene.focus = vars->scene.objects;
	}
	else if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right
		|| key == XK_i || key == XK_o)
	{
		if (key == XK_Up)
			vars->scene.focus->position.y += 100;
		else if (key == XK_Down)
			vars->scene.focus->position.y -= 100;
		else if (key == XK_Left)
			vars->scene.focus->position.x -= 100;
		else if (key == XK_Right)
			vars->scene.focus->position.x += 100;
		else if (key == XK_i)
			vars->scene.focus->position.z -= 100;
		else if (key == XK_o)
			vars->scene.focus->position.z += 100;

		basic_raytracing(&vars->img_vars, &vars->scene);
		put_image_to_window_vars(vars);
	}
}

void	set_up_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, handle_key, vars);
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
		return ;
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



double	vector_dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector	vector_minus(t_vector a, t_vector b)
{
	return ((t_vector){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z});
}

t_vector	vector_tail_head(t_vector tail, t_vector head)
{
	return (vector_minus(head, tail));
}

double	vector_length(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/**
 * @brief 
 * 
 * @param t 
 * @param ray_origin 
 * @param point_on_canvas 
 * @param sphere 
 * @note |O+tD-C|^2 - R^2 = 0;
 *        => a = D^2; b = 2D(O-C); c=|O-C|^2-R^2
 */
void	ray_sphere_intersect(double t[2], t_point ray_origin,
			t_point ray_direction, t_object *sphere)
{
	double		a;
	double		b;
	double		c;
	t_vector	c_to_o;
	double		discriminant;

	c_to_o = vector_minus(ray_origin, sphere->center);
	a = vector_dot_product(ray_direction, ray_direction);
	b = 2 * vector_dot_product(c_to_o, ray_direction);
	c = vector_dot_product(c_to_o, c_to_o) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
	else
	{
		t[0] = (-b + sqrt(discriminant)) / (2 * a);
		t[1] = (-b - sqrt(discriminant)) / (2 * a);
	}
}


t_argb	trace_ray(t_scene *scene, t_point ray_origin, t_vector ray_direction,
		double t_min, double t_max)
{
	double		closest_t;
	double		t[2];
	t_object	*closest_object;
	size_t	i;

	closest_object = NULL;
	closest_t = INFINITY;
	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == Sphere)
		{
			ray_sphere_intersect(t, ray_origin, ray_direction,
				&(scene->objects)[i]);
			if (t[0] >= t_min && t[0] <= t_max && t[0] < closest_t)
			{
				closest_t = t[0];
				closest_object = &(scene->objects[i]);
			}
			if (t[1] >= t_min && t[1] <= t_max && t[1] < closest_t)
			{
				closest_t = t[1];
				closest_object = &(scene->objects[i]);
			}
		}
		++i;
	}
	if (closest_object == NULL)
		return minirt()->background_color;
	else
		return closest_object->color;
}


/**
 * @brief 
 * @ref computer-graphics-from-scratch / 02-basic-raytracing
 */
void	basic_raytracing(t_img_vars *img_vars, t_scene *scene)
{
	t_point	point_on_canvas;
	t_pixel	pixel;

	pixel.y = HEIGHT / 2;
	while (pixel.y >= - HEIGHT / 2)
	{
		pixel.x = - WIDTH / 2;
		while (pixel.x <= WIDTH / 2)
		{
			point_on_canvas = (t_point){.x = pixel.x, .y = pixel.y,
				.z = (double)(-minirt()->eye_canvas_distance)};
			pixel.color = trace_ray(scene, (t_point){0}, point_on_canvas, 1, 
					INFINITY);
			draw_pixel_in_screen_space(img_vars, pixel);
			++pixel.x;
		}
		--pixel.y;
	}
	
}

void	allocate_objects(t_scene *scene, unsigned int object_count)
{
	scene->objects = (t_object *)malloc(object_count * sizeof(t_object));
	scene->object_count = object_count;
}

int	main(int argc, char const *argv[])
{
	t_vars	vars;

	set_up_mlx(&vars);
	set_up_hooks(&vars);

	allocate_objects(&vars.scene, 5);

	vars.scene.objects[0] = (t_object){
		.type = Sphere,
		.color = RED,
		.center = (t_point){0, 0, -3000},
		.radius = 500,
	};
	vars.scene.objects[1] = (t_object){
		.type = Sphere,
		.color = BLUE,
		.center = (t_point){1000, 1000, -5000},
		.radius = 1800
	};
	vars.scene.objects[2] = (t_object){
		.type = Sphere,
		.color = GREEN,
		.center = (t_point){-300, -300, -2500},
		.radius = 300
	};
	vars.scene.objects[3] = (t_object){
		.type = Sphere,
		.color = BLACK,
		.center = (t_point){-1500, 0, -2500},
		.radius = 400
	};

	basic_raytracing(&vars.img_vars, &vars.scene);

	put_image_to_window_vars(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
