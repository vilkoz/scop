/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gl_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:32:45 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 14:33:10 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void			check_gl_error(char *file, int line)
{
	GLenum			error_check_value;

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr,"GL ERROR in file %s:%d - %d \n",
				file, line, (error_check_value));
		exit(-1);
	}
}
