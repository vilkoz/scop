/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 01:23:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/09 12:00:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_H
# define SKYBOX_H

# include "object/object.h"

# ifndef SKYBOX_FOLDER
#  define SKYBOX_FOLDER "res/skybox/"
# endif

t_object		*new_skybox(void);

#endif
