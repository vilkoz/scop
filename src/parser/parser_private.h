/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:29:42 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/07 13:45:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "libft.h"

enum						e_line_type{
	VERTEX,
	TEXTURE_VERTEX,
	NORMAL_VERTEX,
	FACE,
	LINE_TYPE_NUM
};

static t_vector				*face_element_parser(char **lines, int *i,
								char *prefix, void *obj);
struct s_parsed_object		*flatten_vectors(struct s_parsed_object *old);
t_vector					*material_parser(char **lines, int *i,
								char *prefix, void *obj);
t_vector					*face_parser(char **lines, int *i, char *prefix,
								void *obj);

#endif
