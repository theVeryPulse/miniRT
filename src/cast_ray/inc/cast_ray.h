/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:54:11 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 02:58:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_RAY_H
# define CAST_RAY_H

# include "../../color/t_argb.h"
# include "../../ray/t_ray.h"
# include "../../scene/t_scene.h"
# include <stddef.h>
# include <math.h>

t_argb	cast_ray(t_scene *scene, t_ray *ray, uint8_t recursion_depth);

#endif /* CAST_RAY_H */