/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:50:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:55:47 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/inc/libft.h"

/**
 * @brief Moves a pointer through a number in a string.
 *        Format: -+ are optional, if there is a decimal point, there must be at
 *        least one digit before and after it.
 *
 * @param ptr Pointer to the pointer to the starting point of the number in a
 *            string.
 */
extern int skip_number(const char** ptr)
{
    if ((**ptr == '-' || **ptr == '+') && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    if (!ft_isdigit(**ptr))
        return (1);
    while (ft_isdigit(**ptr))
        ++(*ptr);
    if (**ptr == '.' && ft_isdigit(*(*ptr + 1)))
        ++(*ptr);
    while (ft_isdigit(**ptr))
        ++(*ptr);
    if (**ptr == '\0' || **ptr == '\n' || **ptr == ' ')
        return (0);
    else
        return (1);
}
