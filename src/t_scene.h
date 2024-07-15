/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:23 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 17:05:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "t_object.h"
# include <stdint.h>

typedef struct s_scene
{
	/* Array of objects */
	t_object	*objects;
	uint8_t		object_count;
	t_object	*lights;
	uint8_t		light_count;
	t_object	*focus;
	t_object	camera;
}	t_scene;

#endif /* T_SCENE_H */