/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 14:43:42 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "graphics.h"
# include "libft.h"
# include "bmp_loader/bmp_loader.h"

typedef struct	s_object
{
	t_ids		ids;
	t_vector	*v;
	t_vector	*vt;
	t_vector	*vn;
	t_vector	*f;
	t_bmp_data	*bmp;
	t_material	*m;
	t_vertex	pos;
	t_vertex	min;
	t_vertex	max;
	float		scale;
	float		angle;
	void		(*draw)(struct s_object *obj, t_window *win);
}				t_object;

t_object		*new_object(t_parsed_object *p);

/*
** generate_arrays.c
*/

t_vector		*generate_vn_array(t_object *obj);
t_vector		*generate_vt_array(t_object *obj);

/*
** object_fit_to_screen.c
*/

void			obj_find_min_max(t_object *obj);
void			obj_set_center(t_object *obj);

/*
** object_material.c
*/

t_material		*init_object_material(t_material *p);

/*
** object_create_vao.c
*/

void			object_create_vao(t_object *obj);

#endif
