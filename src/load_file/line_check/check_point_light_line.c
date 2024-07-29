/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point_light_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:28:06 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 17:51:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"

/**
 * @brief 
 * 
 * @param iter 
 * @return int
 * @note
 * point light line format: 'L', coordinate, intensity, rgb
 * example:
 *     L -40,0,30                        0.7            255,255,255
 * 
 */
int	check_point_light_line(const char **iter)
{
	if (**iter == 'L' || **iter == 'l')
		++(*iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return (((**iter) != '\n') && ((**iter) != '\0'));
}
