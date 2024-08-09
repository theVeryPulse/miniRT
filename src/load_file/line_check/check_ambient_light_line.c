/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient_light_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:27:11 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:48:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../skip/inc/skip.h"

int check_ambient_light_line(const char** iter)
{
    int error;

    error = 0;
    if (**iter == 'A')
        ++(*iter);
    skip_spaces(iter);
    error |= skip_number(iter);
    skip_spaces(iter);
    error |= skip_rgb(iter);
    skip_spaces(iter);
    return (error || ((**iter != '\n') && (**iter != '\0')));
}
