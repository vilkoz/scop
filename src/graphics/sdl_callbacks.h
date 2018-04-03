/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_callbacks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 08:28:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/03 08:38:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_CALLBACKS_H
# define SDL_CALLBACKS_H

# include "graphics.h"

void				set_window_callback_handle(t_window *win);
void				idle_function(void);
void				timer_function();
void				resize_function(int w, int h);
void				render_function(void);
void				keyboard_function(unsigned char key, int x, int y);

#endif
