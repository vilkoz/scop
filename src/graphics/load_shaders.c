/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:20:24 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 10:56:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "parser/reader.h"
#include "libft.h"

typedef enum	e_shader_compile_error
{
	SHADER_COMPILE_ERROR,
	PROGRAM_COMPILE_ERROR
}				e_shader_error;

static void		check_gl_error(GLuint shaderId, unsigned LINE,
					e_shader_error type)
{
	GLint		ret_status;
	GLint		length;
	GLchar		*pInfo;

	ret_status = 0;
	if (type == SHADER_COMPILE_ERROR)
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &ret_status);
	else if (type == PROGRAM_COMPILE_ERROR)
		glGetProgramiv(shaderId, GL_LINK_STATUS, &ret_status);
	if(ret_status == 0)
	{
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		pInfo = (GLchar*)ft_strnew(length);
		if (type == SHADER_COMPILE_ERROR)
			glGetShaderInfoLog(shaderId, length, &length, pInfo);
		else if (type == PROGRAM_COMPILE_ERROR)
			glGetProgramInfoLog(shaderId, length, &length, pInfo);
		fprintf(stderr, "called at line-%u: Compiler/Linker error: %s", LINE,
				pInfo);
		ft_memdel((void**)&pInfo);
	}
}

static void		compile_shader_from_file(GLuint *id, GLenum shader_type,
					char *filepath)
{
	char	*buf;

	*id = glCreateShader(shader_type);
	buf = read_file_to_string(filepath);
	glShaderSource(*id, 1, (const char*const*)&buf, NULL);
	glCompileShader(*id);
	check_gl_error(*id, __LINE__, SHADER_COMPILE_ERROR);
	ft_strdel(&buf);
}

void			load_shaders(t_ids *ids, char *vertex_filename,
						char *fragment_filename)
{
	compile_shader_from_file(&(ids->vertex_shader), GL_VERTEX_SHADER,
			vertex_filename);
	compile_shader_from_file(&(ids->fragment_shader), GL_FRAGMENT_SHADER,
			fragment_filename);
	ids->program = glCreateProgram();
	glAttachShader(ids->program, ids->vertex_shader);
	glAttachShader(ids->program, ids->fragment_shader);
	glLinkProgram(ids->program);
	check_gl_error(ids->program, __LINE__, PROGRAM_COMPILE_ERROR);
	glUseProgram(ids->program);
	glDeleteShader(ids->vertex_shader);
	glDeleteShader(ids->fragment_shader);
}
