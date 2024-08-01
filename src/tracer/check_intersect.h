/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:15:28 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 19:23:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_INTERSECT_H
# define CHECK_INTERSECT_H

# include "../ray/t_ray.h"
# include "../geometry/inc/geometry.h"
# include "../object/inc/object.h"

extern void	ray_sphere_intersect(
				t_ray *ray,
				t_object *sphere,
				t_object **closest_object,
				double *closest_t);

extern void	ray_plane_intersect(
				t_ray *ray,
				t_object *plane,
				t_object **closest_object,
				double *closest_t);

extern bool	ray_disk_intersect(
				t_ray *ray,
				t_object *disk,
				t_object **closest_object,
				double *closest_t);

extern void	ray_cylinder_intersect(
				t_ray *ray,
				t_object *cylinder,
				t_object **closest_object,
				double *closest_t);

#endif /* CHECK_INTERSECT_H */