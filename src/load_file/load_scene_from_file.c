/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_from_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/28 21:38:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skip/skip.h"
#include "../scene/inc/scene.h"
#include "../t_vars.h"
#include "../object/inc/object.h"
#include "../../lib/libft/inc/libft.h"
#include "../minirt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#ifndef TEST
# define TEST 0
#endif

typedef	struct s_counter
{
	uint32_t	ambient_light;
	uint32_t	camera;
	uint32_t	unique_point_light;
	uint32_t	point_light;
	uint32_t	sphere;
	uint32_t	plane;
	uint32_t	cylinder;
}	t_counter;

int	check_count(t_counter *count)
{
	int	error;

	error = 0;
	if (count->camera < 1)
		error = printf("Error: camera undefined.\n");
	if (count->camera > 1)
		error = printf("Error: multiple cameras defined.\n");
	if (count->ambient_light > 1)
		error = printf("Error: multiple ambient lights defined.\n");
	if (count->unique_point_light > 1)
		error = printf("Error: multiple lights defined with 'L'.\n");
	if (count->ambient_light == 0 && count->unique_point_light == 0)
		printf("Warning: no lights defined.\n");
	if (count->unique_point_light > 0 && count->point_light > 0)
		error = printf("Error: lights defined with both 'L' and 'l'\n");
	return (error > 0);
}

int	check_ambient_light_line(const char **iter)
{
	if (**iter == 'A')
		++(*iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return ((**iter != '\n') && (**iter != '\0'));
}

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * @note
 * camera line format: C, coordinate, angle vector, fov
 * camera line example:
 *     C -50,0,20           0,0,1        70
 * 
 */
int	check_camera_line(const char **iter)
{
	if (**iter == 'C')
		++(*iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	return ((**iter != '\n') && (**iter != '\0'));
}

/**
 * @brief 
 * 
 * @param iter 
 * @return int
 * @note
 * point light line format: 'L', coordinate, intensity, rgb
 * example:
 *     L -40,0,30                        0.7            255,255,255
 * 
 */
int	check_point_light_line(const char **iter)
{
	if (**iter == 'L' || **iter == 'l')
		++(*iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return (((**iter) != '\n') && ((**iter) != '\0'));
}

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * @note
 * sphere line format: 'sp', coordinate, radius, rgb
 * Example:
 * sp 0,0,20                         20             255,0,0
 */
int	check_sphere_line(const char **iter)
{
	if (ft_strncmp("sp ", *iter, 3) == 0)
		(*iter) += 2;
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return (((**iter) != '\n') && ((**iter) != '\0'));
}

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * plane line format: 'pl', coordinate, normal vector, rgv
 * pl 0,0,0             0,1.0,0                     255,0,225
 */
int	check_plane_line(const char **iter)
{
	if (ft_strncmp("pl ", *iter, 3) == 0)
		(*iter) += 2;
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	return (((**iter) != '\n') && ((**iter) != '\0'));
}

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * @note
 * cylinder line format: 'cy', coordinate of center, axis vector, diameter,
 *                       height, rgb
 * cy 50.0,0.0,20.6     0,0,1.0      14.2  21.42    10,0,255
 * 
 */
int	check_cylinder_line(const char **iter)
{
	if (ft_strncmp("cy ", *iter, 3) == 0)
		(*iter) += 2;
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return (((**iter) != '\n') && ((**iter) != '\0'));
}

int	check_line(const char *iter, t_counter *count)
{
	int	line_error;

	line_error = 0;
	skip_spaces(&iter);
	if (ft_strncmp("\n", iter, 2) == 0)
		;
	else if (ft_strncmp("A ", iter, 2) == 0 && ++count->ambient_light)
		line_error |= check_ambient_light_line(&iter);
	else if (ft_strncmp("C ", iter, 2) == 0 && ++count->camera)
		line_error |= check_camera_line(&iter);
	else if (ft_strncmp("L ", iter, 2) == 0 && ++count->unique_point_light)
		line_error |= check_point_light_line(&iter);
	else if (ft_strncmp("l ", iter, 2) == 0 && ++count->point_light)
		line_error |= check_point_light_line(&iter);
	else if (ft_strncmp("sp ",iter, 3) == 0 && ++count->sphere)
		line_error |= check_sphere_line(&iter);
	else if (ft_strncmp("pl ", iter, 3) == 0 && ++count->plane)
		line_error |= check_plane_line(&iter);
	else if (ft_strncmp("cy ", iter, 3) == 0 && ++count->cylinder)
		line_error |= check_cylinder_line(&iter);
	else
		line_error |= 1;
	return (line_error);
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
			printf("Error: line %d unrecognised: %s", line_number,
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

/**
 * @brief 
 * 
 * @param line 
 * @return t_object 
 * @note
 * Ambient light format: 'A', intensity, rgb
 * Example:
 * A  0.2                                         255,255,255   
 * 
 */
void	load_ambient_light_from_line(t_object *a, const char *line)
{
	const char	*iter;

	iter = line;
	if (ft_strncmp("A ", line, 2) == 0)
		iter += 2;
	skip_spaces(&iter);
	*a = ambient_light(ft_atof(iter));
	if (a->intensity < 0.0 || a->intensity > 1.0)
	{
		printf("Error: ambient light intensity out of range [0, 1]: %f\n",
			a->intensity);
		a->error = true;
	}
}

/**
 * @brief 
 * 
 * @param pl 
 * @param line 
 * @note
 * Point light format: 'L', coordinate, intensity, rgb
 * Example:
 *     L -40,0,30                        0.7            255,255,255
 * 
 */
void	load_point_light_from_line(t_object *l, const char *line)
{
	const char	*ptr;
	t_raw_point	position;
	double		intensity;

	ptr = line;
	if (ft_strncmp("L ", line, 2) == 0 || ft_strncmp("l ", line, 2) == 0)
		ptr += 2;
	skip_spaces(&ptr);

	/* Load coordinate */
	position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	position.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	position.z = ft_atof(ptr);
	/* Load coordinate ends */

	skip_number(&ptr);
	skip_spaces(&ptr);
	intensity = ft_atof(ptr);
	*l = point_light(position, intensity);
	if (l->intensity < 0.0 || l->intensity > 1.0)
	{
		printf("Error: point light intensity out of range [0, 1]: %f\n",
			l->intensity);
		l->error = true;
	}
}

void	load_light_from_line(t_object *object, const char *line)
{
	const char	*ptr;

	ptr = line;
	skip_spaces(&ptr);
	if (ft_strncmp("A ", ptr, 2) == 0)
		load_ambient_light_from_line(object, ptr);
	else if (ft_strncmp("L ", ptr, 2) == 0)
		load_point_light_from_line(object, ptr);
	else if (ft_strncmp("l ", ptr, 2) == 0)
		load_point_light_from_line(object, ptr);
	else
		printf("Error: unrecognised light type: %s\n", ptr);
}

void	load_object_from_line(t_object *object, const char *line)
{
	const char	*iter;

	iter = line;
	skip_spaces(&iter);
	if (ft_strncmp("sp ", iter, 3) == 0)
	{
	}
	else if (ft_strncmp("pl ", iter, 3) == 0)
	{
	}
	else if (ft_strncmp("cy ", iter, 3) == 0)
	{
	}
	else
	{
	}
}

/**
 * @brief 
 * 
 * @param camera 
 * @param line 
 * @note
 * Camera line format: 'C', coordinate, angle vector, fov
 * Example:
 * C -50,0,20           0,0,1        70
 * 
 */
void	load_camera_from_line(t_camera *camera, const char *line)
{
	const char	*ptr;

	ptr = line;
	if (ft_strncmp("C ", line, 2) == 0)
		ptr += 2;

	skip_spaces(&ptr);

	/* load coordinate */
	camera->position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->position.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->position.z = ft_atof(ptr);
	/* load coordinate ends */

	skip_number(&ptr);
	skip_spaces(&ptr);

	/* load vector */
	camera->w.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->w.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	camera->w.z = ft_atof(ptr);
	skip_number(&ptr);
	/* load vector ends */

	skip_spaces(&ptr);

	minirt()->fov = ft_atof(ptr);
	if (minirt()->fov < 0.0 || minirt()->fov > 180.0)
	{
		printf("Error: camera field of view out of range (0, 180): %f\n",
			minirt()->fov);
		camera->error = true;
	}
	if (camera->w.x == 0.0 && camera->w.y == 0.0 && camera->w.z == 0.0)
	{
		printf("Error: camera direction vector cannot be zero.\n");
		camera->error = true;
	}
}

void	get_all_lines(t_list **all_lines, const char *filename)
{
	int		file;
	char	*line;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		write(STDOUT_FILENO, "Error: cannot open ", 20);
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
		printf("Error: there should only be 1 argument.\n");
		exit(1);
	}
}

void	check_filename(const char *filename)
{
	if (ft_strlen(filename) <= 3)
	{
		printf("Error: invalid filename: \"%s\"\n", filename);
		exit(1);
	}
	if (!ft_strchr(filename, '.'))
	{
		printf("Error: unrecognised file format.\n");
		exit(1);
	}
	else if (ft_strncmp(".rt", ft_strrchr(filename, '.'), 4))
	{
		printf("Error: unrecognised file format: \"%s\"\n",
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
