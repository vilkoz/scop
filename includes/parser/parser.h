/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 14:08:28 by vrybalko         ###   ########.fr       */
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
** ka - ambient color
** kd - diffuse color
** ks - specular color
** ns - specular exponent = 0..1000
** d or Tr - transperency coeficient (unimplemented)
** illum - only one supported
*/

typedef struct		s_material
{
	t_vertex		ka;
	t_vertex		kd;
	t_vertex		ks;
	float			ns;
}					t_material;

typedef struct		s_parsed_object
{
	t_vector		*v;
	t_vector		*vt;
	t_vector		*vn;
	t_indexes		*f;
	t_material		*mat;
}					t_parsed_object;

t_parsed_object		*obj_file_parser(char *filename);

#endif
