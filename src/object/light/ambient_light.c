/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:54:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:40:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_object.h"

t_object ambient_light(double intensity)
{
    return ((t_object){.category = Light,
                       .type = AmbientLight,
                       .intensity = intensity,
                       .radius = -1,
                       .error = false});
}
