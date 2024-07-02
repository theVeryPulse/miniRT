/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:23 by Philip            #+#    #+#             */
/*   Updated: 2024/07/02 19:53:47 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "t_point.h"

typedef enum e_object_type
{
	Sphere,
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_argb			color;
	t_point			center;
	double			radius;
}	t_object;

typedef struct s_scene
{
	/* Array of objects */
	t_object		*objects;
	unsigned int	object_count;
}	t_scene;

#endif /* T_SCENE_H */