/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/26 01:13:59 by Philip           ###   ########.fr       */
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

void	basic_check(t_list	**all_lines)
{
	uint32_t	line_number = 1;
	t_counter	count;
	const char	*iter;
	t_list		*node;

	count = (t_counter){0};
	node = *all_lines;
	while (node)
	{
		iter = node->content;
		while (*iter == ' ')
			++iter;
		if (!ft_strncmp("\n", iter, 2))
			;
		else if (!ft_strncmp("A ", iter, 2))
			++count.ambient_light;
		else if (!ft_strncmp("C ", iter, 2))
			++count.camera;
		else if (!ft_strncmp("L ", iter, 2))
			++count.unique_point_light;
		else if (!ft_strncmp("sp ", iter, 3))
			++count.sphere;
		else if (!ft_strncmp("pl ", iter, 3))
			++count.plane;
		else if (!ft_strncmp("cy ", iter, 3))
			++count.cylinder;
		else
		{
			printf("Error: line %d unrecognised: %s", line_number,
				(char *)node->content);
			ft_lstclear(all_lines, free);
			exit(1);
		}
		node = node->next;
		++line_number;
	}

	int	error;
	error = 0;

	if (count.camera < 1)
	{
		printf("Error: camera is not defined.\n");
		error = 1;
	}
	if (count.camera > 1)
	{
		printf("Error: multiple cameras defined.\n");
		error = 1;
	}
	if (count.ambient_light > 1)
	{
		printf("Error: multiple ambient lights defined.\n");
		error = 1;
	}
	if (count.unique_point_light > 1)
	{
		printf("Error: multiple point lights defined.\n");
		error = 1;
	}
	if (count.ambient_light == 0 && count.unique_point_light == 0)
	{
		printf("Warning: no lights defined.\n");
	}

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
