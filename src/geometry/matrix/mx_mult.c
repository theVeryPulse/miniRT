/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_mult.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:20:09 by Philip            #+#    #+#             */
/*   Updated: 2024/07/10 22:26:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdarg.h>

/**
 * @brief Multiplies multiple matrices together.
 *
 * @param mx_count The number of matrices to multiply.
 * @param ... The matrices to multiply.
 * @return The product of the matrices.
 */
t_mx	mx_mult(int mx_count, ...)
{
	va_list	ap;
	t_mx	product;
	t_mx	next_mx;

	if (mx_count < 1)
		return ((t_mx){0});
	va_start(ap, mx_count);
	product = va_arg(ap, t_mx);
	while (mx_count > 1)
	{
		next_mx = va_arg(ap, t_mx);
		product = mx_mult_mx(product, next_mx);
		mx_count--;
	}
	va_end(ap);
	return (product);
}
