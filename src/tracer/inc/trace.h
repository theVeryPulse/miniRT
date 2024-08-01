/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:57:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:06:23 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "../../geometry/inc/geometry.h"
# include "../../object/inc/object.h"

extern void	ray_sphere_intersect(
				double t[2],
				t_point ray_origin,
				t_point ray_direction,
				t_object *sphere,
				double a,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

#endif /* TRACE_H */