/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:15:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/25 01:04:31 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "object.h"
#include "matrix.h"
#include <math.h>

static t_window		*g_win;

void				set_window_callback_handle(t_window *win)
{
	g_win = win;
}

void				idle_function(void)
{
	glutPostRedisplay();
}

void				keyboard_function(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	/* printf("key = %d\n", key); */
	if (key == 'w')
		g_win->cam.pos.z += -0.1;
	else if (key == 's')
		g_win->cam.pos.z += +0.1;
	else if (key == 'a')
		g_win->cam.pos.x += 0.1;
	else if (key == 'd')
		g_win->cam.pos.x += -0.1;
	else if (key == 'q')
		g_win->cam.pos.y += -0.1;
	else if (key == 'e')
		g_win->cam.pos.y += 0.1;
	else if (key == 'n')
	{
		g_win->shading_type = (g_win->shading_type + 1) % NUM_SHADING_TYPES;
		printf("shading_type = %d\n", g_win->shading_type);
	}
}

void				timer_function(int count)
{
	char	*title_string;

	if (count == 0)
	{
		g_win->frames = 0;
		return ;
	}
	title_string = (char*)malloc(sizeof(char) * (512 + strlen(g_win->title)));
	sprintf(title_string, "%s: %d fps @ %d x %d", g_win->title, g_win->frames * 4, g_win->w, g_win->h);
	glutSetWindowTitle(title_string);
	free(title_string);
	g_win->frames = 0;
	glutTimerFunc(250, timer_function, 1);
}

void				resize_function(int w, int h)
{
	t_matrix		projection;

	projection = projection_matrix(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	glUniformMatrix4fv(g_win->ids.projection_uniform, 1, GL_FALSE,
			projection.m);
	g_win->w = w;
	g_win->h = h;
	glViewport(0, 0, g_win->w, g_win->h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void				render_function(void)
{
	t_matrix		view;
	t_object		**tmp;
	int				i;

	g_win->frames += 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	INIT_EYE(view);
	translate_matrix(&view, -g_win->cam.pos.x, -g_win->cam.pos.y,
			-g_win->cam.pos.z);
	glUseProgram(g_win->ids.program);
	glUniformMatrix4fv(g_win->ids.view_uniform, 1, GL_FALSE, view.m);
	i = -1;
	while (++i < (int)g_win->obj->size)
	{
		VECTOR_GET_TO(tmp, g_win->obj, i);
		object_draw(*tmp, g_win);
	}
	glutSwapBuffers();
	glutPostRedisplay();
}
