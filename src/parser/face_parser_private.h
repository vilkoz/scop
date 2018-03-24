/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parser_private.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:22:23 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/25 01:23:37 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACE_PARSER_PRIVATE_H
# define FACE_PARSER_PRIVATE_H

# include "libft.h"

t_vector			*face_parser(char **lines, int *i, char *prefix,
						void *obj);

#endif
