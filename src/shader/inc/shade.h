/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:41:17 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 19:13:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_H
# define SHADE_H

# include "../../t_closest.h"
# include "../../ray/t_ray.h"
# include "../../scene/inc/scene.h"

t_argb	shade(t_scene *scene,
			t_ray *ray,
			t_closest *closest,
			uint8_t recursion_depth);

#endif /* SHADE_H */