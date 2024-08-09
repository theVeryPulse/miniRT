/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_vector.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:31:41 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:48:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_VECTOR_H
#define LOAD_VECTOR_H

#include "../../geometry/vector/vector.h"

extern void load_point(t_raw_point* point, const char** line);
extern void load_vector(t_raw_point* point, const char** line);

#endif /* LOAD_VECTOR_H */
