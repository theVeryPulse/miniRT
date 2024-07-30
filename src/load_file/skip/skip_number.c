/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:50:12 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 16:33:17 by Philip           ###   ########.fr       */
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
void	skip_number(const char **ptr)
{
	if ((**ptr == '-' || **ptr == '+')
		&& ft_isdigit(*(*ptr + 1)))
		++(*ptr);
	if (!ft_isdigit(**ptr))
		return ;
	while (ft_isdigit(**ptr))
		++(*ptr);
	if (**ptr == '.' && ft_isdigit(*(*ptr + 1)))
		++(*ptr);
	while (ft_isdigit(**ptr))
		++(*ptr);
}
