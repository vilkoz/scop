/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_visualizer.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 23:35:04 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 23:54:23 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRESS_VISUALIZER_H
# define PROGRESS_VISUALIZER_H

#include "graphics.h"

typedef struct		s_visualizer
{
	SDL_Window		*w;
	SDL_Surface		*s;
	int				*i;
	int				size;
}					t_visualizer;

void		update_visualizer(int *i);
void		init_visualizer(char **lines, int size, int *i);
void		close_visualizer(void);

#endif
