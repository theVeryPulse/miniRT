/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:34:24 by Philip            #+#    #+#             */
/*   Updated: 2024/07/26 00:05:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	if (ft_strncmp(".rt", ft_strrchr(filename, '.'), 4))
	{
		printf("Error: unrecognised file format: \"%s\"\n",
			ft_strrchr(filename, '.'));
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
		printf("%s", line); /* Test */
		ft_lstadd_back(&all_lines, ft_lstnew(line));
		line = get_next_line(file);
	}

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
