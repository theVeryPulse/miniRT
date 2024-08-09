/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:36:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:43:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point.h"

extern t_vector vec_mult(double t, t_vector a)
{
    return ((t_vector){.x = t * a.x, .y = t * a.y, .z = t * a.z});
}
