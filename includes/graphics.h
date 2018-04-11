/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:06:56 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 21:41:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define GL3_PROTOTYPES 1
# include <GL/glew.h>
# ifdef __APPLE__
#  include <SDL.h>
# else
#  include <SDL2/SDL.h>
# endif
# include <stdio.h>
# include "parser/parser.h"

# define W 800
# define H 600
# define VERTEX_SHADER_PATH "shaders/vertex_shader.v.glsl"
# define FRAGMENT_SHADER_PATH "shaders/fragment_shader.f.glsl"
# define WINDOW_NAME "SCOP by vrybalko"

typedef enum		e_shading_type
{
	PHONG_SHADING,
	NORMAL_COLOR_SHADING,
	TEXTURE_SHADING,
	NUM_SHADING_TYPES
}					t_shading_type;

typedef struct		s_ids
{
	GLuint			vertex_shader;
	GLuint			fragment_shader;
	GLuint			program;
	GLuint			vao;
	GLuint			vbo;
	GLuint			vno;
	GLuint			vto;
	GLuint			ebo;
	GLuint			color_buffer;
	GLuint			index_buffer;
	GLuint			model_uniform;
	GLuint			view_uniform;
	GLuint			projection_uniform;
	GLuint			shading_uniform;
	GLuint			shading_transition_uniform;
	GLuint			tex;
	GLuint			second_tex;
	GLuint			cam_pos_uniform;
	GLuint			ka_uniform;
	GLuint			kd_uniform;
	GLuint			ks_uniform;
	GLuint			ns_uniform;
}					t_ids;

typedef struct		s_camera
{
	t_vertex		pos;
	t_vertex		angles;
}					t_camera;

typedef struct		s_sdl_callbacks
{
	void			(*render)(void);
	void			(*timer)(void);
	void			(*resize)(int w, int h);
	void			(*keyboard)(unsigned char key, int x, int y);
	void			(*cleanup)(void *win);
}					t_sdl_callbacks;

typedef struct		s_window
{
	int				w;
	int				h;
	SDL_Window		*handle;
	SDL_GLContext	context;
	t_sdl_callbacks	callbacks;
	char			*title;
	unsigned		frames;
	float			speed_multiplier;
	t_ids			ids;
	t_camera		cam;
	t_vector		*obj;
	int				shading_type;
	int				skybox_num;
	int				enable_rotation;
	float			transition;
}					t_window;

void				init_sdl(int ac, char **av, t_window *win);
void				create_vbo(t_parsed_object *obj, t_ids *ids);
void				load_shaders(t_ids *ids, char *vertex_filename,
						char *fragment_filename);
void				sdl_main_loop(t_window *win);

/*
** check_gl_error.c
*/

void				check_gl_error(char *file, int line);

#endif
