/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_callbacks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:15:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 01:40:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "object/object.h"
#include "matrix.h"
#include <math.h>
#include <time.h>
#include "sdl_keyboard.h"

static t_window		*g_win;

void				set_window_callback_handle(t_window *win)
{
	g_win = win;
}

void				keyboard_function(unsigned char key, int x, int y)
{
	keyboard_action(g_win, key, x, y);
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

	keyboard_function(UNUSED, UNUSED, LAUNCH_PRESSED_KEYS);
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
