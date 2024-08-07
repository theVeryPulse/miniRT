/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:28:44 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:47:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"
#include "../../../lib/libft/inc/libft.h"

/**
 * @brief
 *
 * @param iter
 * @return int
 * plane line format: 'pl', coordinate, normal vector, rgv
 * pl 0,0,0             0,1.0,0                     255,0,225
 */
int check_plane_line(const char** iter)
{
    int error;

    error = 0;
    if (ft_strncmp("pl ", *iter, 3) == 0)
        (*iter) += 2;
    skip_spaces(iter);
    error |= skip_coordinate(iter);
    skip_spaces(iter);
    error |= skip_coordinate(iter);
    skip_spaces(iter);
    error |= skip_rgb(iter);
    skip_spaces(iter);
    return (error || (**iter != '\n' && **iter != '\0'));
}
