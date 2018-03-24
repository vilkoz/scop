/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/24 16:00:39 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "vertex.h"

typedef struct		s_indexes
{
	t_vector		*v;
	t_vector		*n;
	t_vector		*t;
}					t_indexes;

/*
** TODO: add material
*/

typedef struct		s_parsed_object
{
	t_vector		*v;
	t_vector		*vt;
	t_vector		*vn;
	t_indexes		*f;
}					t_parsed_object;

t_parsed_object		*obj_file_parser(char *filename);

#endif
