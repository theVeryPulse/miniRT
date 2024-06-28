/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_coord.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:43:10 by Philip            #+#    #+#             */
/*   Updated: 2024/06/28 20:12:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_COORD_H
# define PX_COORD_H

# include "argb.h"

typedef struct s_pixel
{
	int		x;
	int		y;
	t_argb	color;
}	t_pixel;

#endif