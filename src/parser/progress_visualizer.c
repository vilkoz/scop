/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_visualizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 23:08:33 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/09 14:13:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "progress_visualizer.h"
#include <assert.h>

t_visualizer		**init_visualizer_vars(int *i, int *size)
{
	static t_visualizer	*v = NULL;

	if (v == NULL)
	{
		v = ft_memalloc(sizeof(t_visualizer));
		v->i = i;
		v->size = *size;
	}
	return (&v);
}

void		init_visualizer(char **lines, int size, int *i)
{
	t_visualizer	*v;
	int				calc_size;

	v = *init_visualizer_vars(i, &size);
	if (v->w == NULL)
	{
		assert(SDL_Init(SDL_INIT_VIDEO) == 0);
		v->w = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 500, 300, 0);
		assert(v->w != NULL);
		v->s = SDL_GetWindowSurface(v->w);
		SDL_FillRect(v->s, NULL, 0);
		if (lines)
		{
			calc_size = -1;
			while (lines[++calc_size])
				;
			v->size = calc_size;
		}
	}
}

void		update_visualizer(int *i)
{
	t_visualizer	*v;
	SDL_Rect		rect;
	int				percent;

	v = *init_visualizer_vars(i, i);
	percent = (int)(((float)*(v->i) / (float)v->size) * 100.f);
	rect = (SDL_Rect){(100), (125), percent * 3, (50)};
	SDL_FillRect(v->s, &rect, 0xff0000);
	SDL_UpdateWindowSurface(v->w);
}

void		close_visualizer(void)
{
	t_visualizer	**v;

	v = init_visualizer_vars(0, 0);
	SDL_DestroyWindow((*v)->w);
	SDL_Quit();
	ft_memdel((void**)v);
}
