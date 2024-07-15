/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:11:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 00:58:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "color/inc/argb.h"
# include <stdint.h>

# define DEG_TO_RAD 0.01745329251

typedef struct s_minirt
{
	int		eye_canvas_distance;
	double	fov;
	t_argb	background_color;
	double	image_aspect_ratio;
	double	scale;
}	t_minirt;

extern t_minirt	*minirt(void);
extern void		update_fov(double new_fov);
extern void		minirt_init(void);

#endif /* MINIRT_H */