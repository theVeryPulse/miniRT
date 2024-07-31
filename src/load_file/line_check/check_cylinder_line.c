/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:28:53 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 17:43:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../../lib/libft/inc/libft.h"

/**
 * @brief 
 * 
 * @param iter 
 * @return int 
 * @note
 * cylinder line format: 'cy', coordinate of center, axis vector, diameter,
 *                       height, rgb
 * cy 50.0,0.0,20.6     0,0,1.0      14.2  21.42    10,0,255
 * 
 */
int	check_cylinder_line(const char **iter)
{
	int	error;

	error = 0;
	if (ft_strncmp("cy ", *iter, 3) == 0)
		(*iter) += 2;
	skip_spaces(iter);
	error |= skip_coordinate(iter);
	skip_spaces(iter);
	error |= skip_coordinate(iter);
	skip_spaces(iter);
	error |= skip_number(iter);
	skip_spaces(iter);
	error |= skip_number(iter);
	skip_spaces(iter);
	error |= skip_rgb(iter);
	skip_spaces(iter);
	return (error || (**iter != '\n' && **iter != '\0'));
}
