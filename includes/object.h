/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 00:40:42 by vrybalko         ###   ########.fr       */
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
	int			enable_rotation;
	GLenum		tex_type;
	int			is_cubemap;
}				t_object;

void			object_draw(t_object *obj, t_window *win);
t_object		*new_object(t_parsed_object *p);

#endif
