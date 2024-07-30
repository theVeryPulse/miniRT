/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:08:27 by Philip            #+#    #+#             */
/*   Updated: 2024/07/30 17:07:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKIP_H
# define SKIP_H

extern void	skip_coordinate(const char **iter);
extern int	skip_number(const char **iter);
extern int	skip_rgb(const char **iter);
extern void	skip_spaces(const char **iter);

#endif /* SKIP_H */