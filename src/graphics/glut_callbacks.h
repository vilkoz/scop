/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glut_callbacks.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:17:07 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 02:35:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_CALLBACKS_H
# define GRAPHICS_CALLBACKS_H

# include "graphics.h"

void				set_window_callback_handle(t_window *win);
void				idle_function(void);
void				timer_function(int count);
void				resize_function(int w, int h);
void				render_function(void);
void				keyboard_function(unsigned char key, int x, int y);

#endif
