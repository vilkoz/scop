/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parser_private.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:22:23 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/12 22:50:28 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACE_PARSER_PRIVATE_H
# define FACE_PARSER_PRIVATE_H

# include "libft.h"

enum		e_vertex_type{
	SKIP = -1,
	VERTEX = 0,
	TEXTURE = 1,
	NORMAL = 2
};

# define _THROW(l) exit(fprintf(stderr, "wrong face line: %s!\n", l))
# define THROW_FACE_PARSE_ERROR(l) _THROW(l)

#endif
