/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:57:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 16:18:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include <stdbool.h>

extern bool	trace(t_scene *scene,
				t_point ray_origin,
				t_vector ray_direction,
				double t_min,
				double t_max,
				t_object **closest_object,
				double *closest_t);

#endif /* TRACE_H */