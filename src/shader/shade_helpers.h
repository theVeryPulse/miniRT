/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 17:31:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_HELPERS_H
#define SHADE_HELPERS_H

#include "../geometry/vector/t_point.h"
#include "../object/t_object.h"
#include "../scene/t_scene.h"

extern t_vector normal_on_surface(t_object* obj, t_point intersection);

extern t_vector reflect_ray(t_vector ray, t_vector normal);

extern double calculate_light_intensity(
    t_scene* scene, t_object* tangent_plane, t_vector view);

extern t_argb get_checkerboard_sphere_color(
    t_point pt, t_argb color1, t_argb color2);

#endif /* SHADE_HELPERS_H */