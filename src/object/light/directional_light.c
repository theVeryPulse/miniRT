/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directional_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:01:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:07:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object directional_light(double intensity, t_vector direction)
{
    return ((t_object){
		.type = DirectionalLight,
        .category = Light,
        .intensity = intensity,
        .direction = direction,
        .radius = -1,
        .error = false
	});
}
