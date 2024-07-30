/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_coordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:33 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 15:37:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/skip.h"
#include "../../../lib/libft/inc/libft.h"

void	skip_coordinate(const char **iter)
{
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ((void)--(*iter));
	skip_number(iter);
	if (**iter != ',')
		return ((void)--(*iter));
	++(*iter);
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ((void)--(*iter));
	skip_number(iter);
	if (**iter != ',')
		return ((void)--(*iter));
	++(*iter);
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ((void)--(*iter));
	skip_number(iter);
}
