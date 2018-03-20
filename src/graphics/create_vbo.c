/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vbo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:58:45 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 19:52:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		create_vbo(t_parsed_object *obj, t_ids *ids)
{
	GLenum		ErrorCheckValue;
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR1: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
	glGenVertexArrays(1, &(ids->vao));
	glBindVertexArray(ids->vao);
	glGenBuffers(1, &(ids->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, ids->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
	(void)obj;
}
