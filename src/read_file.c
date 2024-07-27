/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/27 09:15:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#define TEST 1

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
		error = printf("Error: camera is not defined.\n");
	if (count->camera > 1)
		error = printf("Error: multiple cameras defined.\n");
	if (count->ambient_light > 1)
		error = printf("Error: multiple ambient lights defined.\n");
	if (count->unique_point_light > 1)
		error = printf("Error: defining multiple lights with 'L'.\n");
	if (count->ambient_light == 0 && count->unique_point_light == 0)
		printf("Warning: no lights defined.\n");
	return (error > 0);
}

void	skip_spaces(const char **iter)
{
	while (**iter == ' ')
		++(*iter);
}

void	skip_number(const char **iter)
{
	if (**iter == '-' || **iter == '+')
		++(*iter);
	while (ft_isdigit(**iter))
		++(*iter);
	if (**iter == '.')
		++(*iter);
	while (ft_isdigit(**iter))
		++(*iter);
}

void	skip_rgb(const char **iter)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		while (ft_isdigit(**iter))
			++(*iter);
		if (**iter == ',')
			++(*iter);
		++i;
	}
	while (ft_isdigit(**iter))
		++(*iter);
}

void	skip_coordinate(const char **iter)
{
	skip_number(iter);
	if (**iter == ',')
		++(*iter);
	skip_number(iter);
	if (**iter == ',')
		++(*iter);
	skip_number(iter);
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
	if (**iter == 'L')
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
	const char	*iter;
	int			line_error;

	line_number = 1;
	node = *all_lines;
	error = 0;
	while (node)
	{
		line_error = 0;
		iter = node->content;
		skip_spaces(&iter);
		if (!ft_strncmp("\n", iter, 2))
			;
		else if (!ft_strncmp("A ", iter, 2))
		{
			++count->ambient_light;
			line_error |= check_ambient_light_line(&iter);
		}
		else if (!ft_strncmp("C ", iter, 2))
		{
			++count->camera;
			line_error |= check_camera_line(&iter);
		}
		else if (!ft_strncmp("L ", iter, 2))
		{
			++count->unique_point_light;
			line_error |= check_point_light_line(&iter);
		}
		else if (!ft_strncmp("sp ", iter, 3))
			++count->sphere;
		else if (!ft_strncmp("pl ", iter, 3))
			++count->plane;
		else if (!ft_strncmp("cy ", iter, 3))
			++count->cylinder;
		else
			line_error |= 1;
		if (line_error)
			printf("Error: line %d unrecognised: %s", line_number,
				(char *)node->content);
		error |= line_error;
		node = node->next;
		++line_number;
	}
	return (error > 0);
}

void	basic_check(t_list	**all_lines)
{
	t_counter	count;
	int			error;

	count = (t_counter){0};
	error = 0;
	error |= check_format(all_lines, &count);
	error |= check_count(&count);
	printf("A: %u, C: %u, L: %u, sp: %u, pl: %u, cy: %u\n",
		count.ambient_light, count.camera, count.unique_point_light,
		count.sphere, count.plane, count.cylinder); /* Test */
	if (error)
	{
		ft_lstclear(all_lines, free);
		exit(1);
	}
}

void	load_scene(const char* filename)
{
	int		file;
	char	*line;
	t_list	*all_lines;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		write(STDOUT_FILENO, "Error: cannot open ", 20);
		perror(filename);
		exit(1);
	}
	all_lines = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_lstadd_back(&all_lines, ft_lstnew(line));
		line = get_next_line(file);
	}
	basic_check(&all_lines);
	ft_lstclear(&all_lines, free);
}

#if TEST

int	main(int argc, const char **argv)
{
	check_argc(argc);
	check_filename(argv[1]);
	load_scene(argv[1]);
	return (0);
}

#endif
