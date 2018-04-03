/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/03 20:22:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_loader/bmp_loader.h"
#include "object.h"
#include "matrix.h"
#include <math.h>
#include <time.h>

t_vertex		gen_vn(t_object *obj, int v_index)
{
	float		v[4][3];
	float		*val;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
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
		while (++j < 4)
		{
			VECTOR_ADD(v, &(tmp.x));
			VECTOR_ADD(v, &(tmp.y));
			VECTOR_ADD(v, &(tmp.z));
		}
		i += 12;
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
		while (++j < 4)
		{
			pos = NEW_VERTEX(
					*(float*)vector_get(obj->v, i + j*3 + 0),
					*(float*)vector_get(obj->v, i + j*3 + 1),
					*(float*)vector_get(obj->v, i + j*3 + 2));
			tmp = NEW_VERTEX((pos.x - obj->min.x) * obj->scale,
					(pos.y - obj->min.y) * obj->scale, 0);
			VECTOR_ADD(v, &(tmp.x));
			VECTOR_ADD(v, &(tmp.y));
		}
		i += 12;
	}
	return (v);
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

	if (obj->vt)
	{
		glGenBuffers(1, &(obj->ids.vto));
		glBindBuffer(GL_ARRAY_BUFFER, obj->ids.vto);
		glBufferData(GL_ARRAY_BUFFER, obj->vt->size * obj->vt->elem_size,
				(float*)obj->vt->elems, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(2);
	}

	glBindVertexArray(0);
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VAO: %d \n",
				(ErrorCheckValue));
		exit(-1);
	}
}

static void		set_material_uniforms(t_object *obj, t_window *win)
{
	t_vertex		v;

	if (obj->m == NULL)
	{
		v = NEW_VERTEX(0.7, 0.7, 0.7);
		glUniform3fv(win->ids.ka_uniform, 1, (void*)&(v));
		v = NEW_VERTEX(0.7, 0.7, 0.7);
		glUniform3fv(win->ids.kd_uniform, 1, (void*)&(v));
		v = NEW_VERTEX(0.1, 0.1, 0.1);
		glUniform3fv(win->ids.ks_uniform, 1, (void*)&(v));
		glUniform1f(win->ids.ns_uniform, 2.0f);
		return ;
	}
	glUniform3fv(win->ids.ka_uniform, 1, (void*)&(obj->m->ka));
	glUniform3fv(win->ids.kd_uniform, 1, (void*)&(obj->m->kd));
	glUniform3fv(win->ids.ks_uniform, 1, (void*)&(obj->m->ks));
	glUniform1f(win->ids.ns_uniform, obj->m->ns);
}

static void		check_gl_error(int line)
{
	GLenum			error_check_value;

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR %d: Could not create a VBO: %d \n",
				line, (error_check_value));
		exit(-1);
	}
}

void			object_draw(t_object *obj, t_window *win)
{
	t_matrix		model;

	INIT_EYE(model);
	translate_matrix(&model, obj->pos.x, obj->pos.y, obj->pos.z);
	/*             angles  fps                fps     */
	obj->angle += 10.0f * (60.0f * win->speed_multiplier);
	if (obj->angle >= 360.0f)
		obj->angle -= 360.0f;
	rotate_matrix(&model, obj->angle * (M_PI / 180.0f), 'y');
	scale_matrix(&model, obj->scale, obj->scale, obj->scale);
	/* rotate_matrix(&model, 180.0f * (M_PI / 180.0f), 'z'); */
	glBindVertexArray(obj->ids.vao);
	glUniformMatrix4fv(win->ids.model_uniform, 1, GL_FALSE, model.m);
	glUniform1i(win->ids.shading_uniform, win->shading_type);
	set_material_uniforms(obj, win);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)obj->v->size);
	check_gl_error(__LINE__);
	glBindVertexArray(0);
}

# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))

void			obj_find_min_max(t_object *obj)
{
	float		edges[2][3];
	float		*tmp;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		VECTOR_GET_TO(tmp, obj->v, i);
		edges[0][i] = *tmp;
		edges[1][i] = *tmp;
	}
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
}

void			obj_set_center(t_object *obj)
{
	float	scale;
	obj->pos = NEW_VERTEX(-((obj->max.x + obj->min.x) / 2.0f),
		-((obj->max.y + obj->min.y) / 2.0f),
		-((obj->max.z + obj->min.z) / 2.0f));
	scale = 1.0f / (obj->max.x - obj->min.x);
	scale = MIN(1.0f / (obj->max.y - obj->min.y), scale);
	scale = MIN(1.0f / (obj->max.z - obj->min.z), scale);
	obj->scale = scale;
	printf("scale = %f\n", scale);
}

void			init_texture(t_object *obj)
{
	glGenTextures(1, &(obj->ids.tex));
	glBindTexture(GL_TEXTURE_2D, obj->ids.tex);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, obj->bmp->w, obj->bmp->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, obj->bmp->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

t_object		*new_object(t_parsed_object *p)
{
	t_object	*obj;

	obj = ft_memalloc(sizeof(t_object));
	obj->m = p->mat;
	obj->v = p->v;
	obj_find_min_max(obj);
	obj_set_center(obj);
	puts("start_generate");
	if (p->vn && p->vn->size)
		obj->vn = p->vn;
	else
		obj->vn = generate_vn_array(obj);
	printf("obj->vn size: %zu\n", obj->vn->size);
	puts("end_generate");
	puts("start_generate vt");
	if (p->vt && p->vt->size)
		obj->vt = p->vt;
	else
		obj->vt = generate_vt_array(obj);
	puts("end_generate vt");
	object_create_vao(obj);
	obj->bmp = bmp_loader("res/sparcs.bmp");
	init_texture(obj);
	puts("object_create_vao");
	return (obj);
}
