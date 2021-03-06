/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_main_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 23:19:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/10 00:06:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void			sdl_main_loop(t_window *win)
{
	SDL_Event	e;
	int			running;

	running = 1;
	while (running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if ((e.type == SDL_QUIT)
				|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				win->callbacks.keyboard(e.key.keysym.sym, e.type, 0);
			else if (e.type == SDL_WINDOWEVENT &&
				(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
				|| e.window.event == SDL_WINDOWEVENT_RESIZED))
				win->callbacks.resize(e.window.data1, e.window.data2);
		}
		win->callbacks.timer();
		win->callbacks.render();
	}
	win->callbacks.cleanup(win);
}
