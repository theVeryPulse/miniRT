/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:43:41 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:57:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MANAGE_H
# define MLX_MANAGE_H

# include "../../t_vars.h"
# include "../../t_pixel.h"

extern void	set_up_mlx(t_vars *vars);

extern void	put_image_to_window_vars(t_vars *vars);

extern void	draw_pixel_in_raster_space(t_img_vars *img_vars, t_pixel pixel);

extern void	draw_pixel_in_screen_space(t_img_vars *img_vars, t_pixel pixel);

#endif /* MLX_MANAGE_H */