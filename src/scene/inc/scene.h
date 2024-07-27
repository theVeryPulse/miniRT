/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:44:45 by Philip            #+#    #+#             */
/*   Updated: 2024/07/27 13:46:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../t_scene.h"

extern void	allocate_lights(t_scene *scene, unsigned int light_count);
extern void	allocate_objects(t_scene *scene, unsigned int object_count);

#endif
