/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:48:51 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 19:55:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../color/inc/argb.h"
#include "../../../lib/libft/inc/libft.h"
#include <stdio.h>

#define RED_ERROR "\033[91merror: \033[0m"

extern int	load_rgb(t_argb *rgb, const char **line)
{
	int	r;
	int	g;
	int	b;
	int	error;

	error = 0;
	r = ft_atoi(*line);
	*line = ft_strchr(*line, ',') + 1;
	g = ft_atoi(*line);
	*line = ft_strchr(*line, ',') + 1;
	b = ft_atoi(*line);
	printf("  RGB: %d,%d,%d\n", r, g, b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("  "RED_ERROR"RGB out of range [0, 255]: %d,%d,%d\n", r, g, b);
		error = 1;
	}
	*rgb = argb(0xFF, (uint8_t)r, (uint8_t)g, (uint8_t)b);
	return (error > 0);
}
