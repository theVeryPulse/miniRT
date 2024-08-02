/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:23 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 20:45:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "../object/t_object.h"
# include "../camera/t_camera.h"
# include <stdint.h>

typedef struct s_scene
{
	/* Array of objects */
	t_object	*objects;
	uint8_t		object_count;
	t_object	*lights;
	uint8_t		light_count;
	t_object	*focus;
	t_camera	camera;
}	t_scene;

#endif /* T_SCENE_H */