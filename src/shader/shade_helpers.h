/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 16:13:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_HELPERS_H
# define SHADE_HELPERS_H

# include "../geometry/vector/t_point.h"
# include "../object/t_object.h"
# include "../scene/t_scene.h"

extern t_vector	normal_on_surface(t_object *obj, t_point intersection);
extern t_vector	reflect_ray(t_vector ray, t_vector normal);
extern double	calculate_light_intensity(t_scene *scene, t_point point,
					t_vector normal, t_vector view, double specular_exponent);

#endif /* SHADE_HELPERS_H */