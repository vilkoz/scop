/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 08:28:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 16:05:35 by vrybalko         ###   ########.fr       */
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
		SDL_WINDOWPOS_CENTERED, W, H,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	assert(win->handle != NULL);
	set_glut_options(win);
	win->context = SDL_GL_CreateContext(win->handle);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(win->handle);
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	win->enable_rotation = 1;
}

static void		init_camera(t_camera *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 2;
}

static void		get_uniforms_ids(t_ids *ids)
{
	ids->model_uniform = glGetUniformLocation(ids->program, "model");
	ids->view_uniform = glGetUniformLocation(ids->program, "view");
	ids->projection_uniform = glGetUniformLocation(ids->program, "projection");
	ids->shading_uniform = glGetUniformLocation(ids->program, "shading");
	ids->shading_transition_uniform = glGetUniformLocation(ids->program,
			"shading_transition");
	ids->cam_pos_uniform = glGetUniformLocation(ids->program, "camPos");
	ids->ka_uniform = glGetUniformLocation(ids->program, "ka");
	ids->kd_uniform = glGetUniformLocation(ids->program, "kd");
	ids->ks_uniform = glGetUniformLocation(ids->program, "ks");
	ids->ns_uniform = glGetUniformLocation(ids->program, "ns");
}

void			init_sdl(int ac, char **av, t_window *win)
{
	GLenum		err;

	(void)ac;
	(void)av;
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
	load_shaders(&(win->ids), VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	get_uniforms_ids(&(win->ids));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(win->handle);
	resize_function(W, H);
}
