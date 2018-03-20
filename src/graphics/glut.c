/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:05:08 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 00:55:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "glut_callbacks.h"

static void		cleanup()
{
}

static void		set_glut_options(void)
{
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutReshapeFunc(resize_function);
	glutDisplayFunc(render_function);
	glutTimerFunc(0, timer_function, 0);
	glutCloseFunc(cleanup);
	glutIdleFunc(idle_function);
}

static void		init_window(t_window *win)
{
	glutInitWindowSize(W, H);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	if ((win->handle = glutCreateWindow("HELLLO")) < 1)
	{
		fprintf(stderr, "ERROR! COULD NOT CREATE WINDOW!\n");
		exit(1);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void			init_glut(int ac, char **av, t_window *win)
{
	GLenum		err;
	glutInit(&ac, av);
	set_window_callback_handle(win);
	init_window(win);
	set_glut_options();
	glewExperimental = GL_TRUE;
	if ((err = glewInit()) != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	if ((err = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: glew_init: %s \n",
				glewGetErrorString(err));
		/* exit(-1); */
	}
	load_shaders(&(win->ids));
	create_vbo(win->obj, &(win->ids));
}
