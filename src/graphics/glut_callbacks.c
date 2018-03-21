/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:15:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 02:30:42 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../matrix/matrix.h"
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
	g_win->w = w;
	g_win->h = h;
	glViewport(0, 0, g_win->w, g_win->h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void				draw_object(void)
{
	t_matrix		model;
	t_matrix		view;
	t_matrix		projection;

	INIT_EYE(model);
	rotate_matrix(&model, 30.0f * (M_PI / 180.0f), 'x');
	rotate_matrix(&model, 30.0f * (M_PI / 180.0f), 'y');
	INIT_EYE(view);
	translate_matrix(&view, 0, 0, -2);
	projection = projection_matrix(60.0f, (float)(W / H), 0.1f, 100.0f);
	glUseProgram(g_win->ids.program);
	glUniformMatrix4fv(g_win->ids.model_uniform, 1, GL_FALSE, model.m);
	glUniformMatrix4fv(g_win->ids.view_uniform, 1, GL_FALSE, view.m);
	glUniformMatrix4fv(g_win->ids.projection_uniform, 1, GL_FALSE,
			projection.m);
	glDrawElements(GL_TRIANGLE_STRIP, g_win->obj->num_f, GL_UNSIGNED_INT, (GLvoid*)0);
}

void				render_function(void)
{
	g_win->frames += 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* glUseProgram(g_win->ids.program); */
	glBindVertexArray(g_win->ids.vao);
	draw_object();
	/* glDrawElements(GL_TRIANGLE_STRIP, g_win->obj->num_f, GL_UNSIGNED_INT, (GLvoid*)0); */
	glutSwapBuffers();
	glutPostRedisplay();
}
