/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:08:40 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 18:50:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../object/inc/object.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

extern void	load_object_from_line(t_object *object, const char *line)
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
