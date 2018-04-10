/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_keyboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:56:52 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 01:39:58 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_KEYBOARD_H
# define SDL_KEYBOARD_H

# define UNUSED 0
# define LAUNCH_PRESSED_KEYS 1

void				keyboard_action(struct s_window *win, unsigned char key,
						int x, int y);

#endif
