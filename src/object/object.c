/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/23 01:23:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "matrix.h"
#include <math.h>
#include <time.h>

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

t_vertex		gen_vn(t_object *obj, int f_index)
{
	float		v[4][3];
	float		*val;
	int			*v_index;
	int			i[2];

	i[0] = -1;
	int		*index;
	VECTOR_GET_TO(index, obj->f, f_index);
	printf("index: %d %d %d\n", index[0], index[1], index[2]);
	while (++(i[0]) < 4)
	{
		VECTOR_GET_TO(v_index, obj->f, f_index + i[0]);
		printf("v: ");
		i[1] = -1;
		while (++i[1] < 3)
		{
			VECTOR_GET_TO(val, obj->v, *v_index * 3 + i[1]);
			v[i[0]][i[1]] = *val;
			printf(" %f ", v[i[0]][i[1]]);
		}
		puts("");
	}
		puts("");
	for (int k = 0; k < 4; ++k) {
		printf("v: ");
		for (int j = 0; j < 3; ++j) {
			printf(" %f ", v[k][j]);
		}
		puts("");
	}
	puts("");
	return 
		(
			vertex_norm(
				vertex_cross(
					vertex_sub(vertex_new(&(v[0][0])), vertex_new(&(v[1][0]))),
					vertex_sub(vertex_new(&(v[2][0])), vertex_new(&(v[1][0])))
				)
			)
		);
}

t_vector		*generate_vn_array(t_object *obj)
{
	t_vector	*v;
	t_vertex	tmp;
	int			i;
	int			j;

	v = vector_new(0, 0, sizeof(float));
	i = 0;
	while (i < (int)obj->f->size && i < (int)obj->v->size)
	{
		tmp = gen_vn(obj, i);
		printf("tmp: %f %f %f\n", tmp.x, tmp.y, tmp.z);
		j = -1;
		while (++j < 4)
		{
			VECTOR_ADD(v, &(tmp.x));
			VECTOR_ADD(v, &(tmp.y));
			VECTOR_ADD(v, &(tmp.z));
		}
		i += 4;
	}
	return (v);
}

static t_vector	*join_vertices(t_object *obj)
{
	int			i;
	int			j;
	float		*tmp;
	t_vector	*out;

	out = vector_new(0, 0, sizeof(float));
	i = 0;
	while (i < (int)obj->v->size)
	{
		j = -1;
		while (++j < 3)
		{
			VECTOR_GET_TO(tmp, obj->v, i + j);
			VECTOR_ADD(out, tmp);
		}
		j = -1;
		while (++j < 3)
		{
			VECTOR_GET_TO(tmp, obj->vn, i + j);
			VECTOR_ADD(out, tmp);
		}
		i += 3;
	}
	return (out);
}

static void		object_create_vao(t_object *obj)
{
	GLenum		ErrorCheckValue;

	glGenVertexArrays(1, &(obj->ids.vao));
	glBindVertexArray(obj->ids.vao);
	glGenBuffers(1, &(obj->ids.vbo));

	glBindBuffer(GL_ARRAY_BUFFER, obj->ids.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->v->size * obj->v->elem_size,
			(float*)obj->v->elems, GL_STATIC_DRAW);

	glGenBuffers(1, &(obj->ids.ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ids.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->f->size * obj->f->elem_size,
			(int*)obj->f->elems, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
	glDrawElements(GL_QUADS, obj->f->size, GL_UNSIGNED_INT, (GLvoid*)0);
	glEnableVertexAttribArray(0); // isable VAO
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
	puts("ft_memalloc");
	obj->f = flatten_indexes_vector(p->f);
	puts("flatten_indexes_vector");
	obj->v = flatten_vertex_array(p->v, p->num_v);
	puts("flatten_vertex_array");
	if (p->num_vn)
		obj->vn = flatten_vertex_array(p->vn, p->num_vn);
	else
		obj->vn = generate_vn_array(obj);
	printf("obj->vn->size = %zu\n", obj->vn->size);
	if (p->num_vt)
		obj->vt = flatten_vertex_array(p->vt, p->num_vt);
	printf("obj->v->size = %zu\n", obj->v->size);
			float	*tmp;
	for (int i=0; i< (int) obj->v->size; i+=3)
	{
		for (int j=0; j<3; j++)
		{
			VECTOR_GET_TO(tmp, obj->v, j + i);
			printf("\t%f", *tmp);
		}
		puts("");
	}
	obj->v = join_vertices(obj);
	printf("obj->v->size = %zu\n", obj->v->size);
	for (int i=0; i< (int) obj->v->size; i+=3)
	{
		for (int j=0; j<3; j++)
		{
			VECTOR_GET_TO(tmp, obj->v, j + i);
			printf("\t%f", *tmp);
		}
		puts("");
	}
	object_create_vao(obj);
	puts("object_create_vao");
	return (obj);
}
