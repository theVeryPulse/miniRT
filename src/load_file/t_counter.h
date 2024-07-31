/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_counter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:29:42 by Philip            #+#    #+#             */
/*   Updated: 2024/07/31 20:38:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COUNTER_H
# define T_COUNTER_H

# include <stdint.h>

typedef struct s_counter
{
	uint32_t	ambient_light;
	uint32_t	camera;
	uint32_t	unique_point_light;
	uint32_t	point_light;
	uint32_t	sphere;
	uint32_t	plane;
	uint32_t	cylinder;
}	t_counter;

#endif /* T_COUNTER_H */
