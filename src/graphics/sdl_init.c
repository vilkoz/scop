/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 08:28:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/03 19:55:18 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "sdl_callbacks.h"
#include <assert.h>

static void		cleanup(t_window *win)
{
	SDL_GL_DeleteContext(win->context);
	SDL_DestroyWindow(win->handle);
	SDL_Quit();
}

static void		set_glut_options(t_window *win)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	win->callbacks.render = render_function;
	win->callbacks.timer = timer_function;
	win->callbacks.resize = resize_function;
	win->callbacks.keyboard = keyboard_function;
	win->callbacks.cleanup = (void (*)(void*))cleanup;
}

static void		init_window(t_window *win)
{
	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	win->handle = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_OPENGL);
	assert(win->handle != NULL);
	set_glut_options(win);
	win->context = SDL_GL_CreateContext(win->handle);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win->handle);
	glEnable(GL_DEPTH_TEST);
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

static void		init_camera(t_camera *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 2;
}

void			init_sdl(int ac, char **av, t_window *win)
{
	GLenum		err;

	(void)ac;
	(void)av;
	/* glutInit(&ac, av); */
	set_window_callback_handle(win);
	init_window(win);
	init_camera(&(win->cam));
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
