/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:34:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/24 18:08:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include <stdio.h>
static t_vector	*flat_vector_with_indices(t_vector *v, t_vector *indices)
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
		/* printf("index: %d\n", *index); */
		VECTOR_GET_TO(tmp, v, *index - 1);
		VECTOR_ADD(out, &(tmp->x));
		/* printf("vertex: %f", tmp->x); */
		VECTOR_ADD(out, &(tmp->y));
		/* printf(" %f", tmp->y); */
		VECTOR_ADD(out, &(tmp->z));
		/* printf(" %f\n", tmp->z); */
	}
	vector_delete(&v, NULL);
	vector_delete(&indices, NULL);
	return (out);
}

t_parsed_object	*flatten_vectors(t_parsed_object *old)
{
	t_parsed_object	*flat;

	flat = ft_memalloc(sizeof(t_parsed_object));
	flat->v = flat_vector_with_indices(old->v, old->f->v);
	if (old->vn && old->vn->size)
		flat->vn = flat_vector_with_indices(old->vn, old->f->n);
	if (old->vt && old->vt->size)
		flat->vt = flat_vector_with_indices(old->vt, old->f->t);
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
