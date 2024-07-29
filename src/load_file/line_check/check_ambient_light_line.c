/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient_light_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:27:11 by Philip            #+#    #+#             */
/*   Updated: 2024/07/29 17:51:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"

int	check_ambient_light_line(const char **iter)
{
	if (**iter == 'A')
		++(*iter);
	skip_spaces(iter);
	skip_number(iter);
	skip_spaces(iter);
	skip_rgb(iter);
	skip_spaces(iter);
	return ((**iter != '\n') && (**iter != '\0'));
}
