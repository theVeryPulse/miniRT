/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_line.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:14:47 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 20:46:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_FROM_LINE_H
# define LOAD_FROM_LINE_H

# include "../../../camera/t_camera.h"
# include "../../../object/inc/object.h"

extern void	load_camera_from_line(t_camera *camera, const char *line);
extern void	load_light_from_line(t_object *object, const char *line);
extern void	load_object_from_line(t_object *object, const char *line);

#endif /* LOAD_FROM_LINE_H */