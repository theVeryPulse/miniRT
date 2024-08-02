/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_helpers.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:12:42 by Philip            #+#    #+#             */
/*   Updated: 2024/08/02 22:38:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_PRESS_HELPERS_H
# define KEY_PRESS_HELPERS_H

# include "../t_vars.h"

extern void	switch_focus(t_vars *vars);

extern int	clean_exit(int exit_status);

#endif /* KEY_PRESS_HELPERS_H */