/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:30:36 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 17:40:04 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_OBJECT_H
# define T_OBJECT_H

# include "t_point.h"
# include "argb.h"

typedef enum e_object_type
{
	UndefinedObject,
	Sphere,
	AmbientLight,
	PointLight,
	DirectionalLight
}	t_object_type;

typedef enum e_category
{
	UndefinedCategory,
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
}	t_object;

#endif /* T_OBJECT_H */