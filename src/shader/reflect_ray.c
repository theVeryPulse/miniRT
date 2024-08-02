/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:06:35 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 16:07:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../geometry/inc/geometry.h"

/**
 * @brief 
 * 
 * @param normal 
 * @param ray 
 * @return t_vector 
 * @note Equation: R = 2 * dot(N, L) * N - L
 */
extern t_vector	reflect_ray(t_vector ray, t_vector normal)
{
	return (vec_minus(vec_mult(2 * vec_dot(normal, ray), normal), ray));
}
