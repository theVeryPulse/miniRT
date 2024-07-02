/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:11:29 by Philip            #+#    #+#             */
/*   Updated: 2024/07/02 22:09:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "t_scene.h"

typedef struct s_img_vars
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img_vars;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_vars	img_vars;
	t_scene		scene;
}	t_vars;

#endif /* VARS_H */
