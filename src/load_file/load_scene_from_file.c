/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_from_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 22:21:46 by Philip           ###   ########.fr       */
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

int	check_count(t_counter *count)
{
	int	error;

	error = 0;
	if (count->camera < 1)
		error = printf(RED_ERROR"camera undefined.\n");
	if (count->camera > 1)
		error = printf(RED_ERROR"multiple cameras defined.\n");
	if (count->ambient_light > 1)
		error = printf(RED_ERROR"multiple ambient lights defined.\n");
	if (count->unique_point_light > 1)
		error = printf(RED_ERROR"multiple lights defined with 'L'.\n");
	if (count->ambient_light == 0 && count->unique_point_light == 0)
		printf(ORANGE_WARNING"no lights defined.\n");
	if (count->unique_point_light > 0 && count->point_light > 0)
		error = printf(RED_ERROR"lights defined with both 'L' and 'l'\n");
	return (error > 0);
}

/**
 * @brief Checks the format of each line, including:
 *        1) numbers with decimal points,
 *        2) rbg (comma separated integers),
 *        3) coordinate (comma separated numbers with decimal points).
 *        
 *        Does not check the values. For example, does not check if fov is a
 *        positive value.
 * 
 * @param all_lines 
 * @param count 
 * @return int 
 */
int	check_format(t_list **all_lines, t_counter *count)
{
	t_list		*node;
	int			error;
	int			line_number;
	int			line_error;

	line_number = 1;
	node = *all_lines;
	error = 0;
	while (node)
	{
		line_error = check_line(node->content, count);
		if (line_error)
			printf(RED_ERROR"line %d unrecognised: %s", line_number,
				(char *)node->content);
		error |= line_error;
		node = node->next;
		++line_number;
	}
	return (error > 0);
}

t_counter	basic_check(t_list	**all_lines)
{
	t_counter	count;
	int			error;

	count = (t_counter){0};
	error = 0;
	error |= check_format(all_lines, &count);
	error |= check_count(&count);
	printf("A: %u, C: %u, L: %u, sp: %u, pl: %u, cy: %u, l: %u\n",
		count.ambient_light, count.camera, count.unique_point_light,
		count.sphere, count.plane, count.cylinder, count.point_light);
	if (error)
	{
		ft_lstclear(all_lines, free);
		exit(1);
	}
	return (count);
}

void	get_all_lines(t_list **all_lines, const char *filename)
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

// CAMERA
// [x] C(amera)
// LIGHTS
// [x] A(mbient)
// [x] L(ight)
// [x] l(ight)
// OBJECT
// [ ] sp(here)
// [ ] pl(ane)
// [ ] cy(linder)

void	load_scene_from_file(t_vars *vars, const char* filename)
{
	t_list	*all_lines;

	get_all_lines(&all_lines, filename);

	t_counter	count;

	count = basic_check(&all_lines);
	/* initialize objects */
	allocate_objects(&vars->scene, count.cylinder + count.plane + count.sphere);
	allocate_lights(&vars->scene, count.ambient_light + count.point_light
		+ count.unique_point_light);

	t_object	*object;
	t_object	*light;
	t_list		*node;
	const char	*ptr;

	object = vars->scene.objects;
	light = vars->scene.lights;
	node = all_lines;
	while (node)
	{
		ptr = node->content;
		skip_spaces(&ptr);
		if (*ptr == 'C')
			load_camera_from_line(&vars->scene.camera, ptr);
		else if (*ptr == 's' || *ptr == 'p' || *ptr == 'c')
			load_object_from_line(object++, ptr);
		else if (*ptr == 'A' || *ptr == 'L' || *ptr == 'l')
			load_light_from_line(light++, ptr);
		node = node->next;
	}
	/* initialize objects end */

	/* [ ] Check if any lights, object, or camera has error, if yes, free and
	exit */

	ft_lstclear(&all_lines, free);
}

#if TEST

#include "../minirt.h"

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

int	main(int argc, const char **argv)
{
	t_vars	vars;

	minirt_init(&vars);

	/* load scene from file */
	check_argc(argc);
	check_filename(argv[1]);
	load_scene_from_file(&vars, argv[1]);
	/* load scene from file ends */

	return (0);
}

#endif
