/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 23:10:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "mlx_window/inc/mlx_manage.h"
#include "camera/inc/camera.h"
#include "load_file/inc/load_file.h"
#include "scene/inc/scene.h"
#include "object/inc/object.h"
#include "cast_ray/inc/cast_ray.h"
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

extern void	render_image(t_vars *vars);

/* Use this function to load a pre-set scene. */
extern void	load_default_scene(t_scene *scene);

/* Use this function to load a simple test scene. */
extern void	load_test_scene(t_scene *scene);

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
	minirt()->eye_canvas_distance = (WIDTH / 2)
		/ tan((minirt()->fov / 2) * DEG_TO_RAD);
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
