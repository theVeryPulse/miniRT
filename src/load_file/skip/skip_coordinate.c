/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_coordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:41:33 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 22:05:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/skip.h"
#include "../../../lib/libft/inc/libft.h"

void	skip_coordinate(const char **iter)
{
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ;
	skip_number(iter);
	if (**iter != ',')
		return ;
	++(*iter);
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ;
	skip_number(iter);
	if (**iter != ',')
		return ;
	++(*iter);
	if (**iter != '-' && **iter != '+' && !ft_isdigit(**iter))
		return ;
	skip_number(iter);
}
