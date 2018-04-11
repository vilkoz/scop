/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_fit_to_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:19:58 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 22:16:25 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/object.h"
#include "object_fit_to_screen_private.h"

static void		set_edges(float *edges, t_object *obj)
{
	int			i;
	float		*tmp;

	i = -1;
	while (++i < 3)
	{
		VECTOR_GET_TO(tmp, obj->v, i);
		edges[0 + i] = *tmp;
		edges[3 + i] = *tmp;
	}
}

void			obj_find_min_max(t_object *obj)
{
	float		edges[2][3];
	float		*tmp;
	int			i;
	int			j;

	set_edges(((float*)&edges[0][0]), obj);
	i = -1;
	while (++i < (int)obj->v->size / 3)
	{
		j = -1;
		while (++j < 3)
		{
			VECTOR_GET_TO(tmp, obj->v, i * 3 + j);
			edges[0][j] = MIN(edges[0][j], *tmp);
			edges[1][j] = MAX(edges[1][j], *tmp);
		}
	}
	obj->min = vertex_new(&(edges[0][0]));
	obj->max = vertex_new(&(edges[1][0]));
	printf(" min dimentions: %f %f %f\n", obj->min.x, obj->min.y, obj->min.z);
	printf(" max dimentions: %f %f %f\n", obj->max.x, obj->max.y, obj->max.z);
}

void			obj_set_center(t_object *obj)
{
	float	scale;

	obj->pos = NEW_VERTEX(-((obj->max.x + obj->min.x) / 2.0f),
		-((obj->max.y + obj->min.y) / 2.0f),
		-((obj->max.z + obj->min.z) / 2.0f));
	printf(" center: %f %f %f\n", obj->pos.x, obj->pos.y, obj->pos.z);
	scale = 1.0f / (obj->max.x - obj->min.x);
	scale = MIN(1.0f / (obj->max.y - obj->min.y), scale);
	scale = MIN(1.0f / (obj->max.z - obj->min.z), scale);
	obj->scale = scale;
	printf(" scale: %f\n", scale);
}
