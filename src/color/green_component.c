/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   green_component.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:22:03 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:39:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_argb.h"
#include <stdint.h>

/**
 * @brief Retrieves the green component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The green component of the color.
 */
extern uint8_t green_component(t_argb argb)
{
    return (((uint8_t*)&argb)[1]);
}
