/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:30 by Philip            #+#    #+#             */
/*   Updated: 2024/08/09 18:39:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_counter.h"
#include "line_check/inc/line_check.h"
#include "../../lib/libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>

#define RED_ERROR "\033[91merror: \033[0m"
#define ORANGE_WARNING "\033[93mwarning: \033[0m"

static int check_format(t_list** all_lines, t_counter* count);
static int check_count(t_counter* count);

/**
 * @brief
 *
 * @param all_lines
 * @param count
 */
extern void basic_check(t_list** all_lines, t_counter* count)
{
    int error;

    *count = (t_counter){0};
    error = 0;
    error |= check_format(all_lines, count);
    error |= check_count(count);
    printf("A: %u, C: %u, L: %u, sp: %u, pl: %u, cy: %u, l: %u\n",
           count->ambient_light, count->camera, count->unique_point_light,
           count->sphere, count->plane, count->cylinder, count->point_light);
    if (error)
    {
        ft_lstclear(all_lines, free);
        exit(1);
    }
}

/**
 * @brief Checks the format of each line, including:
 *        1) numbers with decimal points,
 *        2) rbg (comma separated integers),
 *        3) coordinate (comma separated numbers with decimal points).
 *
 *        Does not check the values. For example, does not check if fov is a
 *        positive value.
 *
 * @param all_lines
 * @param count
 * @return int
 */
static int check_format(t_list** all_lines, t_counter* count)
{
    t_list* node;
    int     error;
    int     line_number;
    int     line_error;

    line_number = 1;
    node = *all_lines;
    error = 0;
    while (node)
    {
        line_error = check_line(node->content, count);
        if (line_error)
            printf(RED_ERROR "line %d unrecognised: %s", line_number,
                   (char*)node->content);
        error |= line_error;
        node = node->next;
        ++line_number;
    }
    return (error > 0);
}

static int check_count(t_counter* count)
{
    int error;

    error = 0;
    if (count->camera < 1)
        error = printf(RED_ERROR "camera undefined.\n");
    if (count->camera > 1)
        error = printf(RED_ERROR "multiple cameras defined.\n");
    if (count->ambient_light > 1)
        error = printf(RED_ERROR "multiple ambient lights defined.\n");
    if (count->unique_point_light > 1)
        error = printf(RED_ERROR "multiple lights defined with 'L'.\n");
    if (count->ambient_light == 0 && count->unique_point_light == 0)
        printf(ORANGE_WARNING "no lights defined.\n");
    if (count->unique_point_light > 0 && count->point_light > 0)
        error = printf(RED_ERROR "lights defined with both 'L' and 'l'\n");
    if (count->sphere == 0 && count->plane == 0 && count->cylinder == 0)
        printf(ORANGE_WARNING "no objects defined.\n");
    return (error > 0);
}
