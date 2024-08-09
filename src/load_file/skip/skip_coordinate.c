/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_coordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:33 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:55:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/skip.h"
#include "../../../lib/libft/inc/libft.h"

/**
 * @brief Moves a pointer through a coordinate in a string and checks if
 *        coordinate is valid.
 *
 * @param ptr Pointer to the pointer to the start of the coordinate.
 * @return `int` 0 upon success, 1 upon failure.
 */
extern int skip_coordinate(const char** ptr)
{
    if ((**ptr == '-' || **ptr == '+') && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    if (!ft_isdigit(**ptr))
        return (1);
    skip_number(ptr);
    if (**ptr == ',')
        ++(*ptr);
    if ((**ptr == '-' || **ptr == '+') && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    if (!ft_isdigit(**ptr))
        return (1);
    skip_number(ptr);
    if (**ptr == ',')
        ++(*ptr);
    if ((**ptr == '-' || **ptr == '+') && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    if (!ft_isdigit(**ptr))
        return (1);
    skip_number(ptr);
    return (**ptr != '\0' && **ptr != '\n' && **ptr != ' ');
}
