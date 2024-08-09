/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blue_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:22:17 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:37:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_argb.h"
#include <stdint.h>

/**
 * @brief Retrieves the blue component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The blue component of the color.
 */
extern uint8_t blue_component(t_argb argb)
{
    return (((uint8_t*)&argb)[0]);
}
