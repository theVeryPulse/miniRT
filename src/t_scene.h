/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:23 by Philip            #+#    #+#             */
/*   Updated: 2024/07/03 13:36:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "t_point.h"
# include "argb.h"

typedef enum e_object_type
{
	Undefined,
	Sphere,
	AmbientLight,
	PointLight,
	DirectionalLight
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_argb			color;
	t_point			position;
	double			radius;
	double			intensity;
	t_vector		direction;
}	t_object;

typedef struct s_scene
{
	/* Array of objects */
	t_object		*objects;
	unsigned int	object_count;
	t_object		*lights;
	unsigned int	light_count;
	t_object		*focus;
}	t_scene;

#endif /* T_SCENE_H */