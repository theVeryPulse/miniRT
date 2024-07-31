/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:27:49 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 17:42:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"

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
	int	error;

	error = 0;
	if (**iter == 'C')
		++(*iter);
	skip_spaces(iter);
	error |= skip_coordinate(iter);
	skip_spaces(iter);
	error |= skip_coordinate(iter);
	skip_spaces(iter);
	error |= skip_number(iter);
	skip_spaces(iter);
	return (error || ((**iter != '\n') && (**iter != '\0')));
}
