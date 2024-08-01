/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_closest.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:30:30 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 22:31:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CLOSEST_H
# define T_CLOSEST_H

# include "object/t_object.h"

typedef struct s_closest
{
	t_object	*object;
	double		t;
}	t_closest;

#endif /* T_CLOSEST_H */