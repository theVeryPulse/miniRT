/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:30:36 by Philip            #+#    #+#             */
/*   Updated: 2024/07/20 22:51:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_OBJECT_H
# define T_OBJECT_H

# include "geometry/vector/t_point.h"
# include "color/inc/argb.h"
# include <stdbool.h>

typedef enum e_object_type
{
	UndefinedObject,
	CameraType,
	Sphere,
	Plane,
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

	t_category		category;
	t_object_type	type;
	t_point			position;
	t_argb			color;

	/* Light properties */

	double			intensity;
	/* Direction for directional light. Normal for plane */
	t_vector		direction;

	/* Object properties */

	double			radius;
	double			radius_squared;
	double			specular_exponent;
	double			reflectivity;
	bool			is_checkerboard;
}	t_object;

#endif /* T_OBJECT_H */