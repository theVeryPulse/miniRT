/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:15:28 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:22:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_INTERSECT_H
# define CHECK_INTERSECT_H

# include "../geometry/inc/geometry.h"
# include "../object/inc/object.h"

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

extern void	ray_plane_intersect(
				double *t,
				t_point ray_origin,
				t_vector ray_direction,
				t_object *plane,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

extern void	ray_disk_intersect(
				double *t,
				t_point ray_origin,
				t_vector ray_direction,
				t_object *disk,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

extern void	ray_cylinder_intersect(
				double t[2],
				t_point ray_origin,
				t_vector ray_direction,
				t_object *cylinder,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

#endif /* CHECK_INTERSECT_H */