/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:46 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 20:03:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"
#include <stdint.h>

/**
 * @brief Create a int value representing arpg
 * 
 * @param alpha Transparency
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return int (0xAARRGGBB)
 */
extern inline t_argb	argb(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b)
{
	return (*(int *)(uint8_t[4]){b, g, r, alpha});
}

/**
 * @brief Retrieves the alpha component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The alpha component of the color.
 */
extern inline uint8_t	get_a(t_argb argb)
{
	return (((uint8_t *)&argb)[3]);
}

/**
 * @brief Retrieves the red component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The red component of the color.
 */
extern inline uint8_t	red_component(t_argb argb)
{
	return (((uint8_t *)&argb)[2]);
}

/**
 * @brief Retrieves the green component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The green component of the color.
 */
extern inline uint8_t	green_component(t_argb argb)
{
	return (((uint8_t *)&argb)[1]);
}

/**
 * @brief Retrieves the blue component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The blue component of the color.
 */
extern inline uint8_t	blue_component(t_argb argb)
{
	return (((uint8_t *)&argb)[0]);
}
