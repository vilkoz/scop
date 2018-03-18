/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/17 01:06:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
	t_vertex		**f;
}					t_parsed_object;

#endif
