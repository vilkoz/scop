/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vbo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:58:45 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 11:26:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		add_line(t_vector *flat, t_vector *tmp)
{
	int		i;
	int		*tmp_int;

	i = -1;
	while (++i < (int)tmp->size)
	{
		VECTOR_GET_TO(tmp_int, tmp, i);
		VECTOR_ADD(flat, tmp_int);
	}
	while (i % 4 != 0)
	{
		VECTOR_GET_TO(tmp_int, tmp, i % tmp->size + 1);
		VECTOR_ADD(flat, tmp_int);
		i++;
	}
}

t_vector	*flatten_indexes_vector(t_vector *f)
{
	t_vector	*flat;
	t_vector	**tmp;
	int			i;

	flat = vector_new(0, 0, sizeof(int));
	i = -1;
	while (++i < (int)f->size)
	{
		VECTOR_GET_TO(tmp, f, i);
		add_line(flat, *tmp);
	}
	return (flat);
}

/*
** makes one dimentional vector from float3 array @v with given @size
*/

t_vector	*flatten_vertex_array(t_vertex **v, size_t size)
{
	t_vector	*flat;
	int			i;

	flat = vector_new(0, 0, sizeof(float));
	i = -1;
	while (++i < (int)size)
	{
		VECTOR_ADD(flat, &((v[i])->x));
		VECTOR_ADD(flat, &((v[i])->y));
		VECTOR_ADD(flat, &((v[i])->z));
	}
	return (flat);
}

void		create_vbo(t_parsed_object *obj, t_ids *ids)
{
	t_vector	*f;
	t_vector	*v;

	f = flatten_indexes_vector(obj->f);
	v = flatten_vertex_array(obj->v, obj->num_v);
	obj->num_f = f->size;
	GLenum		ErrorCheckValue;
	glGenVertexArrays(1, &(ids->vao));
	glBindVertexArray(ids->vao);
	glGenBuffers(1, &(ids->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, ids->vbo);
	glBufferData(GL_ARRAY_BUFFER, v->size * v->elem_size, (float*)v->elems, GL_STATIC_DRAW);
	glGenBuffers(1, &(ids->ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, f->size * f->elem_size, (int*)f->elems, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}
