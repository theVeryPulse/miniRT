/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:36:29 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:34:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// clang-format off

t_vector vec_cross(t_vector a, t_vector b)
{
    return ((t_vector){(a.y * b.z - a.z * b.y),
                       (a.z * b.x - a.x * b.z),
                       (a.x * b.y - a.y * b.x)});
}
