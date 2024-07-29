/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:27:49 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 17:27:57 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/skip.h"

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * @note
 * camera line format: C, coordinate, angle vector, fov
 * camera line example:
 *     C -50,0,20           0,0,1        70
 * 
 */
int	check_camera_line(const char **iter)
{
	if (**iter == 'C')
		++(*iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_coordinate(iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	return ((**iter != '\n') && (**iter != '\0'));
}
