/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_callbacks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:15:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/10 00:24:24 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "object/object.h"
#include "matrix.h"
#include <math.h>
#include <time.h>

static t_window		*g_win;

static uchar		g_keys[15] = {
	SDLK_w,
	SDLK_s,
	SDLK_a,
	SDLK_d,
	SDLK_q,
	SDLK_e,
	SDLK_j,
	SDLK_l,
	SDLK_i,
	SDLK_k,
	SDLK_u,
	SDLK_o,
	SDLK_m,
	SDLK_r,
	SDLK_n
};

static uchar		g_key_pressed[15] = {0};

void				set_window_callback_handle(t_window *win)
{
	g_win = win;
}

void				key_down(unsigned char key)
{
	int			i;

	i = -1;
	while (++i < (int)(sizeof(g_keys) / sizeof(g_keys[0])))
		if (key == g_keys[i])
			g_key_pressed[i] = 1;
	if (key == SDLK_m)
		g_win->skybox_num = (g_win->skybox_num + 1) % 2;
	if (key == SDLK_r)
		g_win->enable_rotation = (g_win->enable_rotation + 1) % 2;
	if (key == SDLK_n && (fabs(g_win->transition) < 0.001f))
	{
		g_win->shading_type = (g_win->shading_type + 1) % NUM_SHADING_TYPES;
		g_win->transition = 1.f;
	}
}

void				key_up(unsigned char key)
{
	int			i;

	i = -1;
	while (++i < (int)(sizeof(g_keys) / sizeof(g_keys[0])))
		if (key == g_keys[i])
			g_key_pressed[i] = 0;
}

void				keyboard_function(unsigned char key, int x, int y)
{
	(void)y;
	if (x == SDL_KEYDOWN)
		key_down(key);
	else if (x == SDL_KEYUP)
		key_up(key);
}

void				keyboard_check(void)
{
	if (g_key_pressed[0])
		g_win->cam.pos.z += -0.05;
	if (g_key_pressed[1])
		g_win->cam.pos.z += +0.05;
	if (g_key_pressed[2])
		g_win->cam.pos.x += 0.05;
	if (g_key_pressed[3])
		g_win->cam.pos.x += -0.05;
	if (g_key_pressed[4])
		g_win->cam.pos.y += -0.05;
	if (g_key_pressed[5])
		g_win->cam.pos.y += 0.05;
	if (g_key_pressed[6])
		g_win->cam.angles.y += 0.05f;
	if (g_key_pressed[7])
		g_win->cam.angles.y -= 0.05f;
	if (g_key_pressed[8])
		g_win->cam.angles.x += 0.05f;
	if (g_key_pressed[9])
		g_win->cam.angles.x -= 0.05f;
	if (g_key_pressed[10])
		g_win->cam.angles.z += 0.05f;
	if (g_key_pressed[11])
		g_win->cam.angles.z -= 0.05f;
}

void				timer_function()
{
	clock_t		current_clock;

	current_clock = clock();
	g_win->speed_multiplier = (float)(current_clock - g_win->frames) /
		(float)CLOCKS_PER_SEC;
	g_win->frames = current_clock;
	if (g_win->transition > 0)
		g_win->transition -= g_win->speed_multiplier * 30.f;
	if (g_win->transition < 0)
		g_win->transition = 0;
	int wait_time = (1000 / 60) - (int)(g_win->speed_multiplier * 1000);
	if (wait_time > 0)
		SDL_Delay(wait_time);
}

void				resize_function(int w, int h)
{
	t_matrix		projection;

	glUseProgram(g_win->ids.program);
	projection = projection_matrix(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	glUniformMatrix4fv(g_win->ids.projection_uniform, 1, GL_FALSE,
			projection.m);
	g_win->w = w;
	g_win->h = h;
	glViewport(0, 0, g_win->w, g_win->h);
}

void				render_function(void)
{
	t_matrix		view;
	t_object		**tmp;
	int				i;

	keyboard_check();
	g_win->frames += 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	INIT_EYE(view);
	rotate_matrix(&view, g_win->cam.angles.x, 'x');
	rotate_matrix(&view, g_win->cam.angles.y, 'y');
	rotate_matrix(&view, g_win->cam.angles.z, 'z');
	translate_matrix(&view, -g_win->cam.pos.x, -g_win->cam.pos.y,
			-g_win->cam.pos.z);
	glUseProgram(g_win->ids.program);
	glUniformMatrix4fv(g_win->ids.view_uniform, 1, GL_FALSE, view.m);
	glUniform3fv(g_win->ids.cam_pos_uniform, 1, (void*)&(g_win->cam.pos));
	i = -1;
	while (++i < (int)g_win->obj->size)
	{
		VECTOR_GET_TO(tmp, g_win->obj, i);
		(*tmp)->draw(*tmp, g_win);
	}
	SDL_GL_SwapWindow(g_win->handle);
}
