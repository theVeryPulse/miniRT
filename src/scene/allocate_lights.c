/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:35:43 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:09:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_scene.h"
#include "../../lib/libft/inc/libft.h"

extern void allocate_lights(t_scene* scene, unsigned int light_count)
{
    scene->lights = (t_object*)ft_calloc(light_count, sizeof(t_object));
    scene->light_count = light_count;
}
