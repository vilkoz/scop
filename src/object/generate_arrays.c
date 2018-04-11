/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_arrays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:07:23 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 22:12:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/object.h"

static t_vertex	gen_vn(t_object *obj, int v_index)
{
	float		v[4][3];
	float		*val;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			VECTOR_GET_TO(val, obj->v, v_index + i * 3 + j);
			v[i][j] = *val;
		}
	}
	return (vertex_norm(vertex_cross(vertex_sub(vertex_new(&(v[1][0])),
		vertex_new(&(v[0][0]))), vertex_sub(vertex_new(&(v[2][0])),
		vertex_new(&(v[1][0]))))));
}

t_vector		*generate_vn_array(t_object *obj)
{
	t_vector	*v;
	t_vertex	tmp;
	int			i;
	int			j;

	v = vector_new(0, 0, sizeof(float));
	i = 0;
	while (i < (int)obj->v->size)
	{
		tmp = gen_vn(obj, i);
		j = -1;
		while (++j < 3)
		{
			VECTOR_ADD(v, &(tmp.x));
			VECTOR_ADD(v, &(tmp.y));
			VECTOR_ADD(v, &(tmp.z));
		}
		i += 9;
	}
	return (v);
}

t_vector		*generate_vt_array(t_object *obj)
{
	t_vector	*v;
	t_vertex	tmp;
	t_vertex	pos;
	int			i;
	int			j;

	v = vector_new(0, 0, sizeof(float));
	i = 0;
	while (i < ((int)obj->v->size))
	{
		j = -1;
		while (++j < 3)
		{
			pos = NEW_VERTEX(
					*(float*)vector_get(obj->v, i + j * 3 + 0),
					*(float*)vector_get(obj->v, i + j * 3 + 1),
					*(float*)vector_get(obj->v, i + j * 3 + 2));
			tmp = NEW_VERTEX((pos.x - obj->min.x) * obj->scale,
					(pos.y - obj->min.y) * obj->scale, 0);
			VECTOR_ADD(v, &(tmp.x));
			VECTOR_ADD(v, &(tmp.y));
		}
		i += 9;
	}
	return (v);
}
