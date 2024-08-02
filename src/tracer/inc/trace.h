/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:57:12 by Philip            #+#    #+#             */
/*   Updated: 2024/08/01 23:12:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "../../ray/t_ray.h"
# include "../../t_closest.h"
# include <stdbool.h>

extern bool	trace(t_scene *scene, t_ray *ray, t_closest *closest);

#endif /* TRACE_H */