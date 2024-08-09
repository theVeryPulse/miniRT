/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:40:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include "t_mx.h"

t_mx mx_mult(int mx_count, ...);
t_mx mx_mult_mx(t_mx mxa, t_mx mxb);
t_mx mx_transpose(t_mx mx);

#endif
