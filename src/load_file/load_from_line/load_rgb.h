/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_rgb.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:50:50 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:48:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_RGB_H
#define LOAD_RGB_H

#include "../../color/t_argb.h"

extern int load_rgb(t_argb* rgb, const char** line);

#endif /* LOAD_RGB_H */