/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:44:23 by Philip            #+#    #+#             */
/*   Updated: 2024/07/02 22:20:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGB_H
# define ARGB_H

# define BLACK 0x000000
# define BLUE  0x0000ff
# define GREEN 0x00ff00
# define RED   0xff0000
# define WHITE 0xffffff

typedef int	t_argb;

t_argb			argb(unsigned char alpha, unsigned char r, unsigned char g,
					unsigned char b);
unsigned char	get_a(t_argb argb);
unsigned char	get_b(t_argb argb);
unsigned char	get_g(t_argb argb);
unsigned char	get_r(t_argb argb);

#endif