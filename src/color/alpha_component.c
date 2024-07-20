/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_component.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:18:03 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 23:25:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_argb.h"
#include <stdint.h>

/**
 * @brief Retrieves the alpha component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The alpha component of the color.
 */
extern uint8_t	alpha_component(t_argb argb)
{
	return (((uint8_t *)&argb)[3]);
}
