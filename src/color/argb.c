/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:20:54 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 23:25:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_argb.h"
#include <stdint-gcc.h>

/**
 * @brief Create a int value representing arpg
 * 
 * @param alpha Transparency
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return int (0xAARRGGBB)
 */
extern t_argb	argb(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b)
{
	return (*(int *)(uint8_t[4]){b, g, r, alpha});
}
