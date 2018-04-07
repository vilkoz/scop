/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:34:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/07 13:42:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "flatten_vectors_private.h"
#include <stdio.h>

static t_vector	*flat_vector_with_indices(t_vector *v, t_vector *indices,
					t_vertex_type type)
{
	t_vector	*out;
	t_vertex	*tmp;
	int			*index;
	int			i;

	printf("  vector size: %zu, indices size: %zu\n", v->size, indices->size);
	out = vector_new(0, 0, sizeof(float));
	i = -1;
	while (++i < (int)indices->size)
	{
		VECTOR_GET_TO(index, indices, i);
		VECTOR_GET_TO(tmp, v, *index - 1);
		VECTOR_ADD(out, &(tmp->x));
		VECTOR_ADD(out, &(tmp->y));
		if (type != TYPE_TEXTURE)
			VECTOR_ADD(out, &(tmp->z));
	}
	return (out);
}

t_parsed_object	*flatten_vectors(t_parsed_object *old)
{
	t_parsed_object	*flat;

	flat = ft_memalloc(sizeof(t_parsed_object));
	flat->v = flat_vector_with_indices(old->v, old->f->v, TYPE_VERTEX);
	puts(" flattened vertices");
	if (old->vn && old->vn->size)
	{
		flat->vn = flat_vector_with_indices(old->vn, old->f->n, TYPE_NORMAL);
		puts(" flattened normal vectors");
	}
	if (old->vt && old->vt->size)
	{
		flat->vt = flat_vector_with_indices(old->vt, old->f->t, TYPE_TEXTURE);
		puts(" flattened texture vectors");
	}
	vector_delete(&(old->v), NULL);
	vector_delete(&(old->vn), NULL);
	vector_delete(&(old->vt), NULL);
	vector_delete(&(old->f->v), NULL);
	vector_delete(&(old->f->n), NULL);
	vector_delete(&(old->f->t), NULL);
	flat->mat = old->mat;
	ft_memdel((void**)&(old->f));
	ft_memdel((void**)&old);
	return (flat);
}
