/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:04:59 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:38:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/argb.h"

extern inline t_argb color_add(t_argb a, t_argb b)
{
    return (argb(0x00,
	             red_component(a) + red_component(b),
                 green_component(a) + green_component(b),
                 blue_component(a) + blue_component(b)));
}
