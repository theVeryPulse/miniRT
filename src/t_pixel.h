/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pixel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:43:10 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:47:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PIXEL_H
#define T_PIXEL_H

#include "color/inc/argb.h"

typedef struct s_pixel
{
    int    x;
    int    y;
    t_argb color;
} t_pixel;

#endif