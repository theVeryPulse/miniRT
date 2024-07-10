/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:44:23 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 20:29:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGB_H
# define ARGB_H

# include <stdint.h>

# define BLACK 0x000000
# define WHITE 0xffffff

# define BLUE  0x0000ff
# define GREEN 0x00ff00
# define RED   0xff0000

# define MAGENTA 0xff00ff
# define YELLOW  0xffff00
# define CYAN    0x00ffff

typedef int	t_argb;

extern inline t_argb	argb(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
extern inline uint8_t	get_a(t_argb argb);
extern inline uint8_t	blue_component(t_argb argb);
extern inline uint8_t	green_component(t_argb argb);
extern inline uint8_t	red_component(t_argb argb);

extern inline t_argb	color_mult(t_argb color, double intensity);
extern inline t_argb	color_add(t_argb a, t_argb b);

#endif