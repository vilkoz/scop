/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create_vao.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:42:39 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 14:50:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/object.h"
#include "graphics.h"

static void		init_buffer_from_vector(GLuint *id, t_vector *v,
					GLuint attrib_number, GLuint elem_size)
{
	glGenBuffers(1, id);

	glBindBuffer(GL_ARRAY_BUFFER, *id);
	glBufferData(GL_ARRAY_BUFFER, v->size * v->elem_size,
			(float*)v->elems, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib_number, elem_size, GL_FLOAT, GL_FALSE,
			elem_size * sizeof(float), 0);
	glEnableVertexAttribArray(attrib_number);
}

void			object_create_vao(t_object *obj)
{
	glGenVertexArrays(1, &(obj->ids.vao));
	glBindVertexArray(obj->ids.vao);
	init_buffer_from_vector(&(obj->ids.vbo), obj->v, 0, 3);
	if (obj->vn)
		init_buffer_from_vector(&(obj->ids.vno), obj->vn, 1, 3);
	if (obj->vt)
		init_buffer_from_vector(&(obj->ids.vto), obj->vt, 2, 2);
	glBindVertexArray(0);
	check_gl_error(__FILE__, __LINE__);
}

