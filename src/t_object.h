/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:30:36 by Philip            #+#    #+#             */
/*   Updated: 2024/07/15 17:06:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_OBJECT_H
# define T_OBJECT_H

# include "geometry/vector/t_point.h"
# include "color/inc/argb.h"

typedef enum e_object_type
{
	UndefinedObject,
	CameraType,
	Sphere,
	AmbientLight,
	PointLight,
	DirectionalLight
}	t_object_type;

typedef enum e_category
{
	UndefinedCategory,
	Camera,
	Object,
	Light
}	t_category;

typedef struct s_object
{
	/* Common properties */

	t_object_type	type;
	t_category		category;
	t_argb			color;
	t_point			position;

	/* Light properties */

	double			intensity;
	t_vector		direction;

	/* Object properties */

	double			radius;
	double			specular_exponent;
	double			reflectivity;
	double			radius_squared;
}	t_object;

#endif /* T_OBJECT_H */