/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:20:24 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 19:48:50 by vrybalko         ###   ########.fr       */
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

void			check_error(GLuint shaderId, unsigned LINE, e_shader_error type)
{
	GLint bCompiled;

	if (type == SHADER_COMPILE_ERROR)
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &bCompiled);
	else if (type == PROGRAM_COMPILE_ERROR)
		glGetProgramiv(shaderId, GL_LINK_STATUS, &bCompiled);
	if(bCompiled == 0)
	{
		GLint length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		GLchar *pInfo = (GLchar*)malloc(sizeof(GLchar) * (length + 1));
		if (type == SHADER_COMPILE_ERROR)
			glGetShaderInfoLog(shaderId, length, &length, pInfo);
		else if (type == PROGRAM_COMPILE_ERROR)
			glGetProgramInfoLog(shaderId, length, &length, pInfo);
		fprintf(stderr, "called at line-%u: Compiler/Linker error: %s", LINE, pInfo);
		free(pInfo);
	}
}

void		load_shaders(t_ids *ids)
{
	char	*buf;

	ids->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	buf = read_file_to_string(VERTEX_SHADER_PATH);
	glShaderSource(ids->vertex_shader, 1, (const char*const*)&buf, NULL);
	glCompileShader(ids->vertex_shader);
	check_error(ids->vertex_shader, __LINE__, SHADER_COMPILE_ERROR);
	ft_memdel((void*)&buf);
	ids->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	buf = read_file_to_string(FRAGMENT_SHADER_PATH);
	glShaderSource(ids->fragment_shader, 1, (const char*const*)&buf, NULL);
	glCompileShader(ids->fragment_shader);
	check_error(ids->fragment_shader, __LINE__, SHADER_COMPILE_ERROR);
	ft_memdel((void*)&buf);
	ids->program = glCreateProgram();
	glAttachShader(ids->program, ids->vertex_shader);
	glAttachShader(ids->program, ids->fragment_shader);
	glLinkProgram(ids->program);
	check_error(ids->program, __LINE__, PROGRAM_COMPILE_ERROR);
	glUseProgram(ids->program);
	glDeleteShader(ids->vertex_shader);
	glDeleteShader(ids->fragment_shader);
}
