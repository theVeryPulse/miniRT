/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_from_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:08:32 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 23:24:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
#include "scene/inc/scene.h"
#include "geometry/inc/geometry.h"
#include "camera/inc/camera.h"
#include "object/inc/object.h"

void	load_default_scene(t_scene *scene)
{
	scene->camera = camera((t_point){0, 0, 0}, (t_vector){0, 0, 1});
	unsigned int	i = 11;
	allocate_objects(scene, i);
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
	// Right wall
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

	unsigned int object_count = 1;
	allocate_objects(scene, object_count);

	// Wall in back
	// scene->objects[--object_count] = plane((t_p){WHITE,
	// 	(t_point){0.0/960.0, -100.0/960.0, -2000.0/960.0},
	// 	(t_vector){0, 0, 1}, 10.0, 0.0});
	// scene->objects[--object_count] = checkerboard_sphere(
	// 	(t_raw_point){0.01, 0.02, -2}, 0.5, 100, 0.0);
	scene->objects[--object_count] = cylinder((t_c){RED,
		(t_point){0/960.0, 0/960.0, -1500.0/960.0},
		(t_vector){0, 0, 1}, 200.0/960.0, 200.0/960.0, 1.0, 0.0});
	// scene->objects[--object_count] = disk(RED,
		// (t_point){400.0/960.0, 0, -1500.0/960.0},
	// 	(t_vector){0, 0.1, -1}, 200.0/960.0, 1.0, 0.0);

	unsigned int light_count = 2;
	allocate_lights(scene, light_count);
	scene->lights[--light_count] = point_light(
		(t_vector){500.0/960.0, 1000.0/960.0, -1000.0/960.0}, 1);
	scene->lights[--light_count] = ambient_light(0.3);
	scene->focus = scene->objects;
}
// */
