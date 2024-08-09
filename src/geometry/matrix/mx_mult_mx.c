/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_mult_mx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:22:00 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:40:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_mx.h"
#include <stdio.h>

static void calc_mx_product(t_mx* product, t_mx* mxa, t_mx* mxb);

/**
 * @brief Multiplies two matrices.
 *
 * @param mxa The first matrix.
 * @param mxb The second matrix.
 * @return The product of the matrices.
 */
t_mx mx_mult_mx(t_mx mxa, t_mx mxb)
{
    t_mx product;

    if (mxa.col_num != mxb.row_num)
    {
        printf("Error: incorrect number of rows and columns for matrix"
               " multiplication");
        return ((t_mx){0});
    }
    product = (t_mx){.row_num = mxa.row_num, .col_num = mxb.col_num};
    calc_mx_product(&product, &mxa, &mxb);
    return (product);
}

/**
 * @brief Calculates the product of two matrices.
 *
 * @param product Pointer to the production matrix.
 * @param mxa Pointer to the first matrix.
 * @param mxb Pointer to the second matrix.
 */
static void calc_mx_product(t_mx* product, t_mx* mxa, t_mx* mxb)
{
    int    i;
    int    p_row_i;
    int    p_col_i;
    double entry;

    p_row_i = 0;
    while (p_row_i < product->row_num)
    {
        p_col_i = 0;
        while (p_col_i < product->col_num)
        {
            entry = 0;
            i     = 0;
            while (i < mxa->col_num)
            {
                entry += mxa->entries[p_row_i][i] * mxb->entries[i][p_col_i];
                i++;
            }
            product->entries[p_row_i][p_col_i] = entry;
            p_col_i++;
        }
        p_row_i++;
    }
}
