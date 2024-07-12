/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:11:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 23:23:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "color/inc/argb.h"
# include <stdint.h>

typedef struct s_minirt
{
	int		eye_canvas_distance;
	double	fov;
	t_argb	background_color;
}	t_minirt;

extern t_minirt	*minirt(void);
extern void		update_fov(double new_fov);

#endif /* MINIRT_H */