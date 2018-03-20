/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 15:11:42 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
}					t_vertex;

/*
** TODO: add material
*/

typedef struct		s_parsed_object
{
	unsigned int	num_v;
	t_vertex		**v;
	unsigned int	num_vt;
	t_vertex		**vt;
	unsigned int	num_vn;
	t_vertex		**vn;
	unsigned int	num_f;
	t_vector		*f;
}					t_parsed_object;

t_list				*face_parser(char **lines, int *i, char *prefix);
t_list				*face_elment_parser(char **lines, int *i, char *prefix);

t_parsed_object		*obj_file_parser(char *filename);

#endif
