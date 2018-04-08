/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:45:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 16:09:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/object.h"
#include "graphics.h"
#include "matrix.h"
#include <math.h>
#include <time.h>

static void		init_texture(t_object *obj)
{
	glGenTextures(1, &(obj->ids.tex));
	glBindTexture(GL_TEXTURE_2D, obj->ids.tex);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, obj->bmp->w, obj->bmp->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, obj->bmp->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

static void		set_material_uniforms(t_object *obj, t_window *win)
{
	t_vertex		v;

	if (obj->m == NULL)
	{
		v = NEW_VERTEX(0.1, 0.1, 0.1);
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

static void		object_draw(t_object *obj, t_window *win)
{
	t_matrix		model;

	INIT_EYE(model);
	translate_matrix(&model, obj->pos.x, obj->pos.y, obj->pos.z);
	if (win->enable_rotation)
		obj->angle += 30.0f * (1.f / 60.f);
	if (obj->angle >= 360.0f)
		obj->angle -= 360.0f;
	rotate_matrix(&model, obj->angle * (M_PI / 180.0f), 'y');
	scale_matrix(&model, obj->scale, obj->scale, obj->scale);
	glBindVertexArray(obj->ids.vao);
	check_gl_error(__FILE__, __LINE__);
	glUniformMatrix4fv(win->ids.model_uniform, 1, GL_FALSE, model.m);
	check_gl_error(__FILE__, __LINE__);
	glUniform1i(win->ids.shading_uniform, win->shading_type);
	check_gl_error(__FILE__, __LINE__);
	glUniform1f(win->ids.shading_transition_uniform, win->transition);
	check_gl_error(__FILE__, __LINE__);
	set_material_uniforms(obj, win);
	check_gl_error(__FILE__, __LINE__);
	glBindTexture(GL_TEXTURE_2D, obj->ids.tex);
	check_gl_error(__FILE__, __LINE__);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)obj->v->size);
	check_gl_error(__FILE__, __LINE__);
	glBindVertexArray(0);
}

static void		copy_or_generate_arrays(t_object *obj, t_parsed_object *p)
{
	obj->v = p->v;
	obj_find_min_max(obj);
	obj_set_center(obj);
	if (p->vn && p->vn->size)
		obj->vn = p->vn;
	else
	{
		puts(" start generating normals");
		obj->vn = generate_vn_array(obj);
		puts(" end generating normals");
	}
	if (p->vt && p->vt->size)
		obj->vt = p->vt;
	else
	{
		puts(" start generating texture UVs");
		obj->vt = generate_vt_array(obj);
		puts(" end generating texture UVs");
	}
}

t_object		*new_object(t_parsed_object *p)
{
	t_object	*obj;

	obj = ft_memalloc(sizeof(t_object));
	obj->m = init_object_material(p->mat);
	obj->bmp = obj->m->tex;
	copy_or_generate_arrays(obj, p);
	puts(" sizes:\t\tfloats\telements");
	printf("  vertices: \t%zu\t%zu\n", obj->v->size, obj->v->size / 3);
	printf("  normals: \t%zu\t%zu\n", obj->vn->size, obj->vn->size / 3);
	printf("  textures: \t%zu\t%zu\n", obj->vt->size, obj->vt->size / 2);
	object_create_vao(obj);
	glBindVertexArray(obj->ids.vao);
	init_texture(obj);
	glBindVertexArray(0);
	puts(" created VAO for object");
	obj->draw = object_draw;
	return (obj);
}
