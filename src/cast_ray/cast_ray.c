/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:54:22 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 02:57:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../color/t_argb.h"
#include "../geometry/vector/t_point.h"
#include "../t_closest.h"
#include "../ray/t_ray.h"
#include "../scene/t_scene.h"
#include "../tracer/inc/trace.h"
#include "../shader/inc/shade.h"
#include "../minirt.h"
#include <stddef.h>
#include <math.h>

t_argb	cast_ray(t_scene *scene, t_ray *ray, uint8_t recursion_depth)
{
	t_closest	closest;

	closest.object = NULL;
	closest.t = INFINITY;
	if (!trace(scene, ray, &closest))
		return (minirt()->background_color);
	return (shade(scene, ray, &closest, recursion_depth));
}
