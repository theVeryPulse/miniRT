/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pixel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:43:10 by Philip            #+#    #+#             */
/*   Updated: 2024/07/03 11:15:47 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PIXEL_H
# define T_PIXEL_H

# include "argb.h"

typedef struct s_pixel
{
	int		x;
	int		y;
	t_argb	color;
}	t_pixel;

#endif