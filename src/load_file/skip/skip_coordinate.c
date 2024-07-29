/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_coordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:33 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 17:52:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/skip.h"

void	skip_coordinate(const char **iter)
{
	skip_number(iter);
	if (**iter == ',')
		++(*iter);
	skip_number(iter);
	if (**iter == ',')
		++(*iter);
	skip_number(iter);
}
