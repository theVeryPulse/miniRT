/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vars.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:11:29 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:47:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VARS_H
#define T_VARS_H

#include "scene/t_scene.h"

typedef struct s_img_vars
{
    void* img_ptr;
    char* addr;
    int   bits_per_pixel;
    int   line_size;
    int   endian;
} t_img_vars;

typedef struct s_vars
{
    void*      mlx_ptr;
    void*      win_ptr;
    t_img_vars img_vars;
    t_scene    scene;
} t_vars;

#endif /* T_VARS_H */
