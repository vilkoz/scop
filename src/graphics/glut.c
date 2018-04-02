/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:05:08 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/02 23:39:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "glut_callbacks.h"
#include <assert.h>

static void		cleanup(t_window *win)
{
	SDL_GL_DeleteContext(win->context);
	SDL_DestroyWindow(win->handle);
	SDL_Quit();
}

static void		set_glut_options(t_window *win)
{
	/* glutInitContextVersion(4, 0); */
	/* glutInitContextFlags(GLUT_FORWARD_COMPATIBLE); */
	/* glutInitContextProfile(GLUT_CORE_PROFILE); */
	/* glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); */
	/* glutReshapeFunc(resize_function); */
	/* glutDisplayFunc(render_function); */
	/* glutKeyboardFunc(keyboard_function); */
	/* glutTimerFunc(0, timer_function, 0); */
	/* glutCloseFunc(cleanup); */
	/* glutIdleFunc(idle_function); */

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	win->callbacks.render = render_function;
	win->callbacks.resize = resize_function;
	win->callbacks.keyboard = keyboard_function;
	win->callbacks.cleanup = (void (*)(void*))cleanup;
	glEnable(GL_DEPTH_TEST);
	int major_version;
	int minor_version;

	major_version = 0;
	minor_version = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);
	printf("> OpenGL version: %d.%d\n", major_version, minor_version);
}

static void		init_window(t_window *win)
{
	/* glutInitWindowSize(W, H); */
	/* glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); */
	/* if ((win->handle = glutCreateWindow("HELLLO")) < 1) */
	/* { */
	/* 	fprintf(stderr, "ERROR! COULD NOT CREATE WINDOW!\n"); */
	/* 	exit(1); */
	/* } */
	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	win->handle = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_OPENGL);
	assert(win->handle != NULL);
	win->context = SDL_GL_CreateContext(win->handle);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win->handle);
}

static void		init_camera(t_camera *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 2;
}

void			init_glut(int ac, char **av, t_window *win)
{
	GLenum		err;

	(void)ac;
	(void)av;
	/* glutInit(&ac, av); */
	set_window_callback_handle(win);
	init_window(win);
	init_camera(&(win->cam));
	set_glut_options(win);
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
		exit(-1);
	}
	load_shaders(&(win->ids));
	resize_function(W, H);
}
