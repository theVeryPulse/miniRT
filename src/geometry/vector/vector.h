/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:32:03 by Philip            #+#    #+#             */
/*   Updated: 2024/07/23 13:40:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "t_point.h"

extern t_vector	vec_add(t_vector a, t_vector b);
extern t_vector	vec_div(t_vector a, double t);
extern double	vec_dot(t_vector a, t_vector b);
extern t_vector	vec_minus(t_vector a, t_vector b);
extern t_vector	vec_mult(double t, t_vector a);
extern t_vector	vec_cross(t_vector a, t_vector b);

extern double	vec_len(t_vector vec);
extern t_vector	vec_normalized(t_vector vec);
extern void		vec_normalize(t_vector *vec);

#endif /* VECTOR_H */