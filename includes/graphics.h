/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:06:56 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 23:00:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <GL/glew.h>
# include <GL/freeglut.h>
# include <stdio.h>
# include "parser/parser.h"

# define W 800
# define H 600
# define VERTEX_SHADER_PATH "shaders/vertex_shader.v.glsl"
# define FRAGMENT_SHADER_PATH "shaders/fragment_shader.f.glsl"

typedef struct		s_ids
{
	GLuint			vertex_shader;
	GLuint			fragment_shader;
	GLuint			program;
	GLuint			vao;
	GLuint			vbo;
	GLuint			ebo;
	GLuint			color_buffer;
	GLuint			index_buffer;
}					t_ids;

typedef struct		s_window
{
	int				w;
	int				h;
	int				handle;
	char			*title;
	unsigned		frames;
	t_ids			ids;
	t_parsed_object	*obj;
}					t_window;

void				init_glut(int ac, char **av, t_window *win);
void				create_vbo(t_parsed_object *obj, t_ids *ids);
void				load_shaders(t_ids *ids);

#endif