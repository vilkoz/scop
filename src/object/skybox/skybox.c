/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:09:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/12 22:18:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object/object.h"
#include "graphics.h"
#include "bmp_loader/bmp_loader.h"
#include "skybox_private.h"
#include "matrix.h"
#include "object/skybox.h"

static char				*g_filenames[7] = {
	SKYBOX_FOLDER"/lake_skybox/ft.bmp",
	SKYBOX_FOLDER"/lake_skybox/bk.bmp",
	SKYBOX_FOLDER"/lake_skybox/up.bmp",
	SKYBOX_FOLDER"/lake_skybox/dn.bmp",
	SKYBOX_FOLDER"/lake_skybox/lf.bmp",
	SKYBOX_FOLDER"/lake_skybox/rt.bmp",
	NULL
};

static char				*g_second_filenames[7] = {
	SKYBOX_FOLDER"/space_skybox/ft.bmp",
	SKYBOX_FOLDER"/space_skybox/bk.bmp",
	SKYBOX_FOLDER"/space_skybox/up.bmp",
	SKYBOX_FOLDER"/space_skybox/dn.bmp",
	SKYBOX_FOLDER"/space_skybox/lf.bmp",
	SKYBOX_FOLDER"/space_skybox/rt.bmp",
	NULL
};

static float			g_skybox_points[] = {
	50.000000, -50.000000, -50.000000,
	50.000000, -50.000000, 50.000000,
	-50.000000, -50.000000, 50.000000,
	-50.000000, -50.000000, 50.000000,
	-50.000000, -50.000000, -50.000000,
	50.000000, -50.000000, -50.000000,
	50.000000, 50.000000, -50.000000,
	-50.000000, 50.000000, -50.000000,
	-50.000000, 50.000000, 50.000000,
	-50.000000, 50.000000, 50.000000,
	50.000000, 50.000000, 50.000000,
	50.000000, 50.000000, -50.000000,
	50.000000, -50.000000, -50.000000,
	50.000000, 50.000000, -50.000000,
	50.000000, 50.000000, 50.000000,
	50.000000, 50.000000, 50.000000,
	50.000000, -50.000000, 50.000000,
	50.000000, -50.000000, -50.000000,
	50.000000, -50.000000, 50.000000,
	50.000000, 50.000000, 50.000000,
	-50.000000, 50.000000, 50.000000,
	-50.000000, 50.000000, 50.000000,
	-50.000000, -50.000000, 50.000000,
	50.000000, -50.000000, 50.000000,
	-50.000000, -50.000000, 50.000000,
	-50.000000, 50.000000, 50.000000,
	-50.000000, 50.000000, -50.000000,
	-50.000000, 50.000000, -50.000000,
	-50.000000, -50.000000, -50.000000,
	-50.000000, -50.000000, 50.000000,
	50.000000, 50.000000, -50.000000,
	50.000000, -50.000000, -50.000000,
	-50.000000, -50.000000, -50.000000,
	-50.000000, -50.000000, -50.000000,
	-50.000000, 50.000000, -50.000000,
	50.000000, 50.000000, -50.000000
};

static t_material		*init_skybox_material(void)
{
	t_material	*m;

	m = ft_memalloc(sizeof(t_material));
	m->ka = NEW_VERTEX(1.0f, 1.0f, 1.0f);
	m->kd = NEW_VERTEX(0.0f, 0.0f, 0.0f);
	m->ks = NEW_VERTEX(0.0f, 0.0f, 0.0f);
	m->ns = 50.f;
	return (m);
}

static void				skybox_draw(t_object *obj, t_window *win)
{
	t_matrix		model;
	t_matrix		view;
	t_matrix		projection;

	glBindVertexArray(obj->ids.vao);
	glUseProgram(obj->ids.program);
	projection = projection_matrix(45.0f, (float)win->w / (float)win->h,
			0.1f, 100.0f);
	glUniformMatrix4fv(obj->ids.projection_uniform, 1, GL_FALSE, projection.m);
	INIT_EYE(model);
	glUniformMatrix4fv(obj->ids.model_uniform, 1, GL_FALSE, model.m);
	check_gl_error(__FILE__, __LINE__);
	INIT_EYE(view);
	rotate_matrix(&view, win->cam.angles.x, 'x');
	rotate_matrix(&view, win->cam.angles.y, 'y');
	rotate_matrix(&view, win->cam.angles.z, 'z');
	glUniformMatrix4fv(obj->ids.view_uniform, 1, GL_FALSE, view.m);
	check_gl_error(__FILE__, __LINE__);
	glBindTexture(GL_TEXTURE_CUBE_MAP,
			win->skybox_num ? obj->ids.second_tex : obj->ids.tex);
	check_gl_error(__FILE__, __LINE__);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)obj->v->size);
	check_gl_error(__FILE__, __LINE__);
	glBindVertexArray(0);
}

static void				get_uniforms_ids(t_ids *ids)
{
	ids->model_uniform = glGetUniformLocation(ids->program, "model");
	ids->view_uniform = glGetUniformLocation(ids->program, "view");
	ids->projection_uniform = glGetUniformLocation(ids->program, "projection");
}

t_object				*new_skybox(void)
{
	t_object		*obj;

	obj = ft_memalloc(sizeof(t_object));
	obj->m = init_skybox_material();
	obj->v = vector_new((void*)&(g_skybox_points[0]), sizeof(g_skybox_points),
			sizeof(float));
	printf("skybox v size: %zu %zu\n", obj->v->size, obj->v->size / 3);
	obj_find_min_max(obj);
	obj_set_center(obj);
	obj->scale = 1.f;
	printf("skybox scale: %f\n", obj->scale);
	obj->vn = generate_vn_array(obj);
	obj->vt = generate_vt_array(obj);
	object_create_vao(obj);
	glBindVertexArray(obj->ids.vao);
	load_cubemap(&(obj->ids.tex), &(g_filenames[0]));
	load_cubemap(&(obj->ids.second_tex), &(g_second_filenames[0]));
	glBindVertexArray(0);
	obj->draw = skybox_draw;
	load_shaders(&(obj->ids), "shaders/skybox.v.glsl", "shaders/skybox.f.glsl");
	get_uniforms_ids(&(obj->ids));
	return (obj);
}
