/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:17:37 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 17:38:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H

# include "../geometry/vector/t_point.h"

typedef enum e_ray_type
{
	UndefinedRayType,
	PrimaryRay,
	ReflectionRay,
	ShadowRay,
}	t_ray_type;

typedef struct s_ray
{
	t_point		origin;
	/* Normalized direction vector */
	t_vector	direction;
	double		t_min;
	double		t_max;
	double		direction_squared;
}	t_ray;

#endif /* T_RAY_H */
