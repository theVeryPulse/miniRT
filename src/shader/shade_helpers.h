/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 16:01:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_HELPERS_H
# define SHADE_HELPERS_H

# include "../geometry/vector/t_point.h"
# include "../object/t_object.h"

extern t_vector	normal_on_surface(t_object *obj, t_point intersection);

#endif /* SHADE_HELPERS_H */