/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:35:19 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 23:36:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../geometry/vector/vector.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

static void	check_is_number(const char *ptr);

extern void	load_point(t_raw_point *point, const char **line)
{
	skip_spaces(line);
	check_is_number(*line);
	point->x = ft_atof(*line);
	*line = ft_strchr(*line, ',') + 1;
	check_is_number(*line);
	point->y = ft_atof(*line);
	*line = ft_strchr(*line, ',') + 1;
	check_is_number(*line);
	point->z = ft_atof(*line);
	skip_number(line);
}

extern void	load_vector(t_raw_point *point, const char **line)
{
	load_point(point, line);
}

static void	check_is_number(const char *ptr)
{
	if (!ft_isdigit(*ptr) && *ptr != '-' && *ptr != '+')
		printf("Error: expected number, got: %s\n", ptr);
}
