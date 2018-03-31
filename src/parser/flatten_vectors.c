/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:34:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 18:02:56 by vrybalko         ###   ########.fr       */
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

	out = vector_new(0, 0, sizeof(float));
	i = -1;
	while (++i < (int)indices->size)
	{
		VECTOR_GET_TO(index, indices, i);
		/* printf("index = %d\n", *index); */
		VECTOR_GET_TO(tmp, v, *index - 1);
		VECTOR_ADD(out, &(tmp->x));
		VECTOR_ADD(out, &(tmp->y));
		if (type != TYPE_TEXTURE)
			VECTOR_ADD(out, &(tmp->z));
	}
	vector_delete(&v, NULL);
	vector_delete(&indices, NULL);
	return (out);
}

t_parsed_object	*flatten_vectors(t_parsed_object *old)
{
	t_parsed_object	*flat;

	flat = ft_memalloc(sizeof(t_parsed_object));
	puts("start v");
	flat->v = flat_vector_with_indices(old->v, old->f->v, TYPE_VERTEX);
	puts("start normals");
	if (old->vn && old->vn->size)
		flat->vn = flat_vector_with_indices(old->vn, old->f->n, TYPE_NORMAL);
	puts("start textures");
	if (old->vt && old->vt->size)
		flat->vt = flat_vector_with_indices(old->vt, old->f->t, TYPE_TEXTURE);
	/* vector_delete(&(old->v), NULL); */
	/* vector_delete(&(old->vn), NULL); */
	/* vector_delete(&(old->vt), NULL); */
	/* vector_delete(&(old->f->v), NULL); */
	/* vector_delete(&(old->f->n), NULL); */
	/* vector_delete(&(old->f->t), NULL); */
	ft_memdel((void**)&(old->f));
	ft_memdel((void**)&old);
	return (flat);
}
