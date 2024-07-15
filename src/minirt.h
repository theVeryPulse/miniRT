/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:11:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 17:04:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "color/inc/argb.h"
# include <stdint.h>

# define DEG_TO_RAD 0.01745329251

typedef struct s_minirt
{
	int			eye_canvas_distance;
	double		fov;
	t_argb		background_color;
	double		image_aspect_ratio;
	double		scale;
	uint32_t	unit_one;
}	t_minirt;

extern t_minirt	*minirt(void);
extern void		update_fov(double new_fov);
extern void		minirt_init(void);

#endif /* MINIRT_H */