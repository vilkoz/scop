/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:09:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 12:53:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object.h"
#include "bmp_loader/bmp_loader.h"
#include "skybox_private.h"
#include "matrix.h"

static char		*g_filenames[7] = {
	"res/sor_lake1/lake1_ft.bmp",
	"res/sor_lake1/lake1_bk.bmp",
	"res/sor_lake1/lake1_up.bmp",
	"res/sor_lake1/lake1_dn.bmp",
	"res/sor_lake1/lake1_lf.bmp",
	"res/sor_lake1/lake1_rt.bmp",
	NULL
};

static GLenum	g_sides[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

static float	g_skybox_points[] = {
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

static void				load_cubemap_side(GLuint texture_id, GLenum side, 
		char *filename)
{
	t_bmp_data		*bmp;

	(void)texture_id;
	bmp = bmp_loader(filename);
	if (bmp == NULL)
	{
		fprintf(stderr, "I COULD NOT LOAD CUBEMAP WITHOUT RESOURSES!\n");
		exit(1);
	}
	glTexImage2D(side, 0, GL_RGB, bmp->w, bmp->h, 0, GL_BGR, GL_UNSIGNED_BYTE,
			bmp->data);
}

static void				load_cubemap(t_object *obj)
{
	int		i;

	glGenTextures(1, &(obj->ids.tex));
	glBindTexture(GL_TEXTURE_CUBE_MAP, obj->ids.tex);
	i = -1;
	while (++i < 6)
		load_cubemap_side(obj->ids.tex, g_sides[i], g_filenames[i]);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	/* translate_matrix(&model, win->cam.pos.x, win->cam.pos.y, */
	/* 		win->cam.pos.z); */
	/* scale_matrix(&model, obj->scale, obj->scale, obj->scale); */
	glUniformMatrix4fv(obj->ids.model_uniform, 1, GL_FALSE, model.m);
	check_gl_error(__LINE__);
	INIT_EYE(view);
	/* translate_matrix(&view, -g_win->cam.pos.x, -g_win->cam.pos.y, */
	/* 		-g_win->cam.pos.z); */
	rotate_matrix(&view, win->cam.angles.x, 'x');
	rotate_matrix(&view, win->cam.angles.y, 'y');
	rotate_matrix(&view, win->cam.angles.z, 'z');
	glUniformMatrix4fv(obj->ids.view_uniform, 1, GL_FALSE, view.m);
	check_gl_error(__LINE__);
	glBindTexture(obj->tex_type, obj->ids.tex);
	check_gl_error(__LINE__);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)obj->v->size);
	check_gl_error(__LINE__);
	glBindVertexArray(0);
}

static void		get_uniforms_ids(t_ids *ids)
{
	ids->model_uniform = glGetUniformLocation(ids->program, "model");
	ids->view_uniform = glGetUniformLocation(ids->program, "view");
	ids->projection_uniform = glGetUniformLocation(ids->program, "projection");
}

t_object		*new_skybox(void)
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
	obj->enable_rotation = 0;
	obj->is_cubemap = 1;
	obj->vn = generate_vn_array(obj);
	obj->vt = generate_vt_array(obj);
	object_create_vao(obj);
	glBindVertexArray(obj->ids.vao);
	load_cubemap(obj);
	glBindVertexArray(0);
	obj->tex_type = GL_TEXTURE_CUBE_MAP;
	obj->draw = skybox_draw;
	load_shaders(&(obj->ids), "shaders/skybox.v.glsl", "shaders/skybox.f.glsl");
	get_uniforms_ids(&(obj->ids));
	return (obj);
}
