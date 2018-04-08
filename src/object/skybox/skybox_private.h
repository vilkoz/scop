/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 01:14:00 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 14:35:28 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_PRIVATE_C
# define SKYBOX_PRIVATE_C

# include "object/object.h"

void			obj_find_min_max(t_object *obj);
void			obj_set_center(t_object *obj);
t_vector		*generate_vn_array(t_object *obj);
t_vector		*generate_vt_array(t_object *obj);
void			object_create_vao(t_object *obj);
void			load_cubemap(GLuint *tex_id, char **filenames);

#endif
