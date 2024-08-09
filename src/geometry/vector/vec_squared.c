/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_squared.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:49:50 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:43:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point.h"

extern double vec_squared(t_vector vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
