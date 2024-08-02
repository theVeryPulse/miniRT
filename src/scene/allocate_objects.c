/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:36:58 by Philip            #+#    #+#             */
/*   Updated: 2024/07/27 13:46:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_scene.h"
#include "../../lib/libft/inc/libft.h"

extern void	allocate_objects(t_scene *scene, unsigned int object_count)
{
	scene->objects = (t_object *)ft_calloc(object_count, sizeof(t_object));
	scene->object_count = object_count;
}
