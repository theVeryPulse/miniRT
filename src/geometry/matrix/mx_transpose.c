/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_transpose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:17:41 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:33:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_mx.h"

/**
 * @brief Transposes the given matrix.
 *
 * @param mx The matrix to be transposed.
 * @return The transposed matrix.
 */
t_mx mx_transpose(t_mx mx)
{
    t_mx mx_t;
    int  i;
    int  j;

    mx_t.col_num = mx.row_num;
    mx_t.row_num = mx.col_num;
    i = 0;
    while (i < MAX_ROW)
    {
        j = 0;
        while (j < MAX_COL)
        {
            mx_t.entries[i][j] = mx.entries[j][i];
            j++;
        }
        i++;
    }
    return (mx_t);
}
