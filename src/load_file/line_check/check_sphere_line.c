/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:28:30 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:47:29 by Philip           ###   ########.fr       */
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
 * sphere line format: 'sp', coordinate, radius, rgb
 * Example:
 * sp 0,0,20                         20             255,0,0
 */
int check_sphere_line(const char** iter)
{
    int error;

    error = 0;
    if (ft_strncmp("sp ", *iter, 3) == 0)
        (*iter) += 2;
    skip_spaces(iter);
    error |= skip_coordinate(iter);
    skip_spaces(iter);
    error |= skip_number(iter);
    skip_spaces(iter);
    error |= skip_rgb(iter);
    skip_spaces(iter);
    return (error || (**iter != '\n' && **iter != '\0'));
}
