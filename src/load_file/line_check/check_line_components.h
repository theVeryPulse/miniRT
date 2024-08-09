/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_components.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:33:01 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 16:47:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_LINE_COMPONENTS_H
#define CHECK_LINE_COMPONENTS_H

extern int check_ambient_light_line(const char** iter);

extern int check_camera_line(const char** iter);

extern int check_cylinder_line(const char** iter);

extern int check_plane_line(const char** iter);

extern int check_point_light_line(const char** iter);

extern int check_sphere_line(const char** iter);

#endif /* CHECK_LINE_COMPONENTS_H */