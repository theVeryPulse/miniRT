/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:08:55 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 19:12:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vars.h"
#include "minirt.h"
#include "window.h"
#include "mlx_window/inc/mlx_manage.h"
#include "key_press/inc/key_press.h"
#include "geometry/inc/geometry.h"
#include "load_file/inc/load_file.h"
#include "../lib/libft/inc/libft.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */
#include <math.h>   /* tan */

#define RED_ERROR "\033[91merror: \033[0m"

/*  Defined in render_image.c */
extern void render_image(t_vars* vars);

/* Defined in load_scene_from_code.c
 * Use this function to load a pre-set scene.
 * To use this function: use this line in main
 *     load_test_scene(&vars.scene);
 */
extern void load_default_scene(t_scene* scene);

/* Defined in load_scene_from_code.c
 * Use this function to load a simple test scene.
 * To use this function: use this line in main
 *    load_test_scene(&vars.scene);
 */
// extern void	load_test_scene(t_scene *scene);

static void precompute_values(t_scene* scene);
static void check_argc(int argc);
static void check_filename(const char* filename);

int main(int argc, char const* argv[])
{
    t_vars vars;

    check_argc(argc);
    check_filename(argv[1]);
    minirt_init(&vars);
    load_scene_from_file(&vars.scene, argv[1]);
    // load_default_scene(&vars.scene);
    precompute_values(&vars.scene);
    set_up_mlx(&vars);
    set_up_hooks(&vars);
    render_image(&vars);
    put_image_to_window_vars(&vars);
    mlx_loop(vars.mlx_ptr);
    return (0);
}

static void check_argc(int argc)
{
    if (argc == 1)
        exit(0);
    else if (argc > 2)
    {
        printf(RED_ERROR "there should only be 1 argument.\n");
        exit(1);
    }
}

static void check_filename(const char* filename)
{
    if (ft_strlen(filename) <= 3)
    {
        printf(RED_ERROR "invalid filename: \"%s\"\n", filename);
        exit(1);
    }
    if (!ft_strchr(filename, '.'))
    {
        printf(RED_ERROR "unrecognised file format.\n");
        exit(1);
    }
    else if (ft_strncmp(".rt", ft_strrchr(filename, '.'), 4))
    {
        printf(RED_ERROR "unrecognised file format: \"%s\"\n",
               ft_strrchr(filename, '.'));
        exit(1);
    }
}

static void precompute_values(t_scene* scene)
{
    t_object* o;

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
