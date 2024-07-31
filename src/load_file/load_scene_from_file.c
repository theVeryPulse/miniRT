/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_from_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 15:40:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_counter.h"
#include "skip/inc/skip.h"
#include "line_check/inc/line_check.h"
#include "load_from_line/inc/load_from_line.h"

#include "../scene/inc/scene.h"
#include "../object/inc/object.h"
#include "../t_vars.h"
#include "../minirt.h"
#include "../../lib/libft/inc/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#ifndef TEST
# define TEST 0
#endif

#define RED_ERROR "\033[91merror: \033[0m"
#define ORANGE_WARNING "\033[93mwarning: \033[0m"

/* Defined in basic_check.c */

extern void	basic_check(t_list	**all_lines, t_counter *count);

static void	get_all_lines(t_list **all_lines, const char *filename)
{
	int					file;
	char				*line;
	static const char	*cannot_open_message = RED_ERROR"cannot open ";

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		write(STDOUT_FILENO, cannot_open_message,
			ft_strlen(cannot_open_message));
		perror(filename);
		exit(1);
	}
	*all_lines = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_lstadd_back(all_lines, ft_lstnew(line));
		line = get_next_line(file);
	}
	close(file);
}

void	load_scene_from_lines(t_scene *scene, t_list *all_lines)
{
	t_object	*object;
	t_object	*light;
	t_list		*node;
	const char	*ptr;

	object = scene->objects;
	light = scene->lights;
	node = all_lines;
	while (node)
	{
		ptr = node->content;
		skip_spaces(&ptr);
		if (*ptr == 'C')
			load_camera_from_line(&scene->camera, ptr);
		else if (*ptr == 's' || *ptr == 'p' || *ptr == 'c')
			load_object_from_line(object++, ptr);
		else if (*ptr == 'A' || *ptr == 'L' || *ptr == 'l')
			load_light_from_line(light++, ptr);
		node = node->next;
	}
}

void	check_scene(t_scene *scene)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	while (i < scene->object_count)
		error |= scene->objects[i++].error;
	i = 0;
	while (i < scene->light_count)
		error |= scene->lights[i++].error;
	error |= scene->camera.error;
	if (error)
	{
		free(scene->objects);
		free(scene->lights);
		exit(1);
	}
}

void	load_scene_from_file(t_scene *scene, const char* filename)
{
	t_list		*all_lines;
	t_counter	count;

	get_all_lines(&all_lines, filename);
	basic_check(&all_lines, &count);
	allocate_objects(scene, count.cylinder + count.plane + count.sphere);
	allocate_lights(scene, count.ambient_light + count.point_light
		+ count.unique_point_light);
	load_scene_from_lines(scene, all_lines);
	ft_lstclear(&all_lines, free);
	check_scene(scene);
	scene->focus = scene->objects;
}
