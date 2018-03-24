/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/24 18:14:32 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "matrix.h"
#include <math.h>
#include <time.h>

/* t_vertex		gen_vn(t_object *obj, int f_index) */
/* { */
/* 	float		v[4][3]; */
/* 	float		*val; */
/* 	int			*v_index; */
/* 	int			i[2]; */

/* 	i[0] = -1; */
/* 	int		*index; */
/* 	VECTOR_GET_TO(index, obj->f, f_index); */
/* 	printf("index: %d %d %d\n", index[0], index[1], index[2]); */
/* 	while (++(i[0]) < 4) */
/* 	{ */
/* 		VECTOR_GET_TO(v_index, obj->f, f_index + i[0]); */
/* 		printf("v: "); */
/* 		i[1] = -1; */
/* 		while (++i[1] < 3) */
/* 		{ */
/* 			VECTOR_GET_TO(val, obj->v, *v_index * 3 + i[1]); */
/* 			v[i[0]][i[1]] = *val; */
/* 			printf(" %f ", v[i[0]][i[1]]); */
/* 		} */
/* 		puts(""); */
/* 	} */
/* 		puts(""); */
/* 	for (int k = 0; k < 4; ++k) { */
/* 		printf("v: "); */
/* 		for (int j = 0; j < 3; ++j) { */
/* 			printf(" %f ", v[k][j]); */
/* 		} */
/* 		puts(""); */
/* 	} */
/* 	puts(""); */
/* 	return */ 
/* 		( */
/* 			vertex_norm( */
/* 				vertex_cross( */
/* 					vertex_sub(vertex_new(&(v[0][0])), vertex_new(&(v[1][0]))), */
/* 					vertex_sub(vertex_new(&(v[2][0])), vertex_new(&(v[1][0]))) */
/* 				) */
/* 			) */
/* 		); */
/* } */

/* t_vector		*generate_vn_array(t_object *obj) */
/* { */
/* 	t_vector	*v; */
/* 	t_vertex	tmp; */
/* 	int			i; */
/* 	int			j; */

/* 	v = vector_new(0, 0, sizeof(float)); */
/* 	i = 0; */
/* 	while (i < (int)obj->f->size && i < (int)obj->v->size) */
/* 	{ */
/* 		tmp = gen_vn(obj, i); */
/* 		printf("tmp: %f %f %f\n", tmp.x, tmp.y, tmp.z); */
/* 		j = -1; */
/* 		while (++j < 4) */
/* 		{ */
/* 			VECTOR_ADD(v, &(tmp.x)); */
/* 			VECTOR_ADD(v, &(tmp.y)); */
/* 			VECTOR_ADD(v, &(tmp.z)); */
/* 		} */
/* 		i += 4; */
/* 	} */
/* 	return (v); */
/* } */

/* static t_vector	*join_vertices(t_object *obj) */
/* { */
/* 	int			i; */
/* 	int			j; */
/* 	float		*tmp; */
/* 	t_vector	*out; */

/* 	out = vector_new(0, 0, sizeof(float)); */
/* 	i = 0; */
/* 	while (i < (int)obj->v->size) */
/* 	{ */
/* 		j = -1; */
/* 		while (++j < 3) */
/* 		{ */
/* 			VECTOR_GET_TO(tmp, obj->v, i + j); */
/* 			VECTOR_ADD(out, tmp); */
/* 		} */
/* 		j = -1; */
/* 		while (++j < 3) */
/* 		{ */
/* 			VECTOR_GET_TO(tmp, obj->vn, i + j); */
/* 			VECTOR_ADD(out, tmp); */
/* 		} */
/* 		i += 3; */
/* 	} */
/* 	return (out); */
/* } */

static void		object_create_vao(t_object *obj)
{
	GLenum		ErrorCheckValue;

	glGenVertexArrays(1, &(obj->ids.vao));
	glBindVertexArray(obj->ids.vao);
	glGenBuffers(1, &(obj->ids.vbo));

	glBindBuffer(GL_ARRAY_BUFFER, obj->ids.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->v->size * obj->v->elem_size,
			(float*)obj->v->elems, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	if (obj->vn)
	{
		glGenBuffers(1, &(obj->ids.vno));
		glBindBuffer(GL_ARRAY_BUFFER, obj->ids.vno);
		glBufferData(GL_ARRAY_BUFFER, obj->vn->size * obj->vn->elem_size,
				(float*)obj->vn->elems, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(0);
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}

void			object_draw(t_object *obj, t_window *win)
{
	t_matrix		model;

	INIT_EYE(model);
	scale_matrix(&model, 0.2, 0.2, 0.2);
	rotate_matrix(&model, ((float)clock() / 1e6f) * 50.0f * (M_PI / 180.0f), 'y');
	/* rotate_matrix(&model, 180.0f * (M_PI / 180.0f), 'z'); */
	glBindVertexArray(obj->ids.vao);
	glUniformMatrix4fv(win->ids.model_uniform, 1, GL_FALSE, model.m);
	/* glDrawElements(GL_QUADS, obj->f->size, GL_UNSIGNED_INT, (GLvoid*)0); */
	glDrawArrays(GL_QUADS, 0, (GLsizei)obj->v->size);
	glBindVertexArray(0);
	GLenum ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}

t_object		*new_object(t_parsed_object *p)
{
	t_object	*obj;

	obj = ft_memalloc(sizeof(t_object));
	obj->v = p->v;
	if (p->vn && p->vn->size)
		obj->vn = p->vn;
	/* else */
	/* 	obj->vn = generate_vn_array(obj); */
	if (p->vt && p->vt->size)
		obj->vt = p->vt;
	/* obj->v = join_vertices(obj); */
	object_create_vao(obj);
	puts("object_create_vao");
	return (obj);
}
