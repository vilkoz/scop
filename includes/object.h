/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 19:33:09 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "graphics.h"
# include "libft.h"

typedef struct	s_object
{
	t_ids		ids;
	t_vector	*v;
	t_vector	*vt;
	t_vector	*vn;
	t_vector	*f;
	t_vertex	pos;
}				t_object;

void			object_draw(t_object *obj, t_window *win);
t_object		*new_object(t_parsed_object *p);

#endif
