/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:42:11 by Philip            #+#    #+#             */
/*   Updated: 2024/07/28 21:14:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/inc/libft.h"

void	skip_rgb(const char **iter)
{
	if (!ft_isdigit(**iter))
		return ;
	while (ft_isdigit(**iter))
		++(*iter);
	if (**iter == ',')
		++(*iter);
	if (!ft_isdigit(**iter))
		return ;
	while (ft_isdigit(**iter))
		++(*iter);
	if (**iter == ',')
		++(*iter);
	if (!ft_isdigit(**iter))
		return ;
	while (ft_isdigit(**iter))
		++(*iter);
}
