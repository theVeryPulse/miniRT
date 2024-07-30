/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:50:12 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 15:45:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/inc/libft.h"

void	skip_number(const char **iter)
{
	if (**iter == '-' || **iter == '+')
		++(*iter);
	if (!ft_isdigit(**iter))
		return ((void)--(*iter));
	while (ft_isdigit(**iter))
		++(*iter);
	if (**iter == '.')
		++(*iter);
	if (!ft_isdigit(**iter))
		return ((void)--(*iter));
	while (ft_isdigit(**iter))
		++(*iter);
}
