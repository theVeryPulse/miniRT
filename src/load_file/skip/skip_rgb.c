/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:42:11 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:55:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/inc/libft.h"

/**
 * @brief Skips a RGB value in a string. Format: Three positive intergers
 *        separated by commas, range [0, 255].
 *
 * @param ptr Pointer to the pointer to the starting point of the RGB value in a
 *            string.
 * @return `int` 0 upon success, 1 otherwise.
 */
int skip_rgb(const char** ptr)
{
    if (!ft_isdigit(**ptr))
        return (1);
    while (ft_isdigit(**ptr))
        ++(*ptr);
    if (**ptr == ',' && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    else
        return (1);
    while (ft_isdigit(**ptr))
        ++(*ptr);
    if (**ptr == ',' && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    else
        return (1);
    while (ft_isdigit(**ptr))
        ++(*ptr);
    if (**ptr == '\0' || **ptr == '\n' || **ptr == ' ')
        return (0);
    else
        return (1);
}
