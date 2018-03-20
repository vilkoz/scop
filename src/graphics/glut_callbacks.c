/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:15:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 19:51:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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

void				render_function(void)
{
	g_win->frames += 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); */
	glBindVertexArray(g_win->ids.vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	/* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0); */
	glutSwapBuffers();
	glutPostRedisplay();
}
