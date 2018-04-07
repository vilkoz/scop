/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:09:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 01:30:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object.h"
#include "bmp_loader/bmp_loader.h"
#include "skybox_private.h"

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
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X
};

static float	g_skybox_points[] = {
	1.000000, -1.000000, -1.000000,
	1.000000, -1.000000, 1.000000,
	-1.000000, -1.000000, 1.000000,

	-1.000000, -1.000000, -1.000000,
	1.000000, -1.000000, -1.000000,
	1.000000, -1.000000, 1.000000,

	1.000000, 1.000000, -0.999999,
	-1.000000, 1.000000, -1.000000,
	-1.000000, 1.000000, 1.000000,

	0.999999, 1.000000, 1.000001,
	1.000000, 1.000000, -0.999999,
	-1.000000, 1.000000, -1.000000,

	1.000000, -1.000000, -1.000000,
	1.000000, 1.000000, -0.999999,
	0.999999, 1.000000, 1.000001,

	1.000000, -1.000000, 1.000000,
	1.000000, -1.000000, -1.000000,
	1.000000, 1.000000, -0.999999,

	1.000000, -1.000000, 1.000000,
	0.999999, 1.000000, 1.000001,
	-1.000000, 1.000000, 1.000000,

	-1.000000, -1.000000, 1.000000,
	1.000000, -1.000000, 1.000000,
	0.999999, 1.000000, 1.000001,

	-1.000000, -1.000000, 1.000000,
	-1.000000, 1.000000, 1.000000,
	-1.000000, 1.000000, -1.000000,

	-1.000000, -1.000000, -1.000000,
	-1.000000, -1.000000, 1.000000,
	-1.000000, 1.000000, 1.000000,

	1.000000, 1.000000, -0.999999,
	1.000000, -1.000000, -1.000000,
	-1.000000, -1.000000, -1.000000,

	-1.000000, 1.000000, -1.000000,
	1.000000, 1.000000, -0.999999,
	1.000000, -1.000000, -1.000000
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

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
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
	i = -1;
	while (++i < 6)
		load_cubemap_side(obj->ids.tex, g_sides[i], g_filenames[i]);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

t_object		*new_skybox(void)
{
	t_object		*obj;

	obj = ft_memalloc(sizeof(t_object));
	obj->m = init_skybox_material();
	obj->v = vector_new((void*)&(g_skybox_points[0]), sizeof(g_skybox_points),
			sizeof(float));
	obj_find_min_max(obj);
	obj_set_center(obj);
	obj->enable_rotation = 0;
	obj->is_cubemap = 1;
	obj->vn = generate_vn_array(obj);
	obj->vt = generate_vt_array(obj);
	object_create_vao(obj);
	glBindVertexArray(obj->ids.vao);
	load_cubemap(obj);
	glBindVertexArray(0);
	obj->tex_type = GL_TEXTURE_CUBE_MAP;
	return (obj);
}
