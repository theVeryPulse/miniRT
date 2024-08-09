/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:05:02 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:33:13 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/argb.h"

// clang-format off

extern inline t_argb color_mult(t_argb color, double factor)
{
    return (argb(0x00,
	             red_component(color) * factor,
                 green_component(color) * factor,
                 blue_component(color) * factor));
}
