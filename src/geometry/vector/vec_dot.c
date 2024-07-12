/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:29:26 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 22:55:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point.h"

extern double	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}