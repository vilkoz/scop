/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubemap_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:01:14 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 22:12:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object/object.h"
#include "bmp_loader/bmp_loader.h"
#include "skybox_private.h"
#include "matrix.h"

static GLenum	g_sides[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

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
	printf(" loaded skybox side %d: w %d, h %d, name %s\n", side - g_sides[0],
			bmp->w, bmp->h, filename);
	glTexImage2D(side, 0, GL_RGB, bmp->w, bmp->h, 0, GL_BGR, GL_UNSIGNED_BYTE,
			bmp->data);
	check_gl_error(__FILE__, __LINE__);
}

void					load_cubemap(GLuint *tex_id, char **filenames)
{
	int		i;

	glGenTextures(1, tex_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *tex_id);
	i = -1;
	while (++i < 6)
		load_cubemap_side(*tex_id, g_sides[i], filenames[i]);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
