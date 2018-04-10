/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:18:54 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 01:36:06 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "graphics.h"
# include "bmp_loader/bmp_loader.h"

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

static void			key_down(t_window *win, unsigned char key)
{
	int			i;

	i = -1;
	while (++i < (int)(sizeof(g_keys) / sizeof(g_keys[0])))
		if (key == g_keys[i])
			g_key_pressed[i] = 1;
	if (key == SDLK_m)
		win->skybox_num = (win->skybox_num + 1) % 2;
	if (key == SDLK_r)
		win->enable_rotation = (win->enable_rotation + 1) % 2;
	if (key == SDLK_n && (fabs(win->transition) < 0.001f))
	{
		win->shading_type = (win->shading_type + 1) % NUM_SHADING_TYPES;
		win->transition = 1.f;
	}
}

static void			key_up(unsigned char key)
{
	int			i;

	i = -1;
	while (++i < (int)(sizeof(g_keys) / sizeof(g_keys[0])))
		if (key == g_keys[i])
			g_key_pressed[i] = 0;
}

static void			keyboard_check(t_window *win)
{
	if (g_key_pressed[0])
		win->cam.pos.z += -0.05;
	if (g_key_pressed[1])
		win->cam.pos.z += +0.05;
	if (g_key_pressed[2])
		win->cam.pos.x += 0.05;
	if (g_key_pressed[3])
		win->cam.pos.x += -0.05;
	if (g_key_pressed[4])
		win->cam.pos.y += -0.05;
	if (g_key_pressed[5])
		win->cam.pos.y += 0.05;
	if (g_key_pressed[6])
		win->cam.angles.y += 0.05f;
	if (g_key_pressed[7])
		win->cam.angles.y -= 0.05f;
	if (g_key_pressed[8])
		win->cam.angles.x += 0.05f;
	if (g_key_pressed[9])
		win->cam.angles.x -= 0.05f;
	if (g_key_pressed[10])
		win->cam.angles.z += 0.05f;
	if (g_key_pressed[11])
		win->cam.angles.z -= 0.05f;
}

void				keyboard_action(t_window *win, unsigned char key,
						int x, int y)
{
	if (y != 0)
	{
		keyboard_check(win);
		return ;
	}
	if (x == SDL_KEYDOWN)
		key_down(win, key);
	else if (x == SDL_KEYUP)
		key_up(key);
}
