/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:50:39 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:56:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void skip_spaces(const char** iter)
{
    while (**iter == ' ')
        ++(*iter);
}
