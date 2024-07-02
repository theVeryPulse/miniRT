/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:11:08 by Philip            #+#    #+#             */
/*   Updated: 2024/07/02 19:38:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "argb.h"
# include <stdint.h>

typedef struct s_minirt
{
	int		eye_canvas_distance;
	double	fov;
	t_argb	background_color;
}	t_minirt;

extern t_minirt	*minirt(void);

#endif /* MINIRT_H */