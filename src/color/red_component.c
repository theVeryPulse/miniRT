/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_component.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:21:36 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 23:25:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_argb.h"
#include <stdint.h>

/**
 * @brief Retrieves the red component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The red component of the color.
 */
extern uint8_t	red_component(t_argb argb)
{
	return (((uint8_t *)&argb)[2]);
}
