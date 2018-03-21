/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_matrices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 01:18:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 02:18:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"
#include <math.h>

void		scale_matrix(t_matrix *m, float x, float y, float z)
{
	t_matrix	scale;

	INIT_EYE(scale);
	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;
	ft_memcpy((void*)m->m, matrix_mul(m, &scale).m, sizeof(m->m));
}

void		translate_matrix(t_matrix *m, float x, float y, float z)
{
	t_matrix	translation;

	INIT_EYE(translation);
	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
	ft_memcpy((void*)m->m, matrix_mul(m, &translation).m, sizeof(m->m));
}

void		rotate_matrix(t_matrix *m, float angle, char axes)
{
	float		cosa;
	float		sina;
	t_matrix	rotation;

	cosa = (float)cos(angle);
	sina = (float)sin(angle);
	if (axes == 0 || axes == 'x' || axes == 'X')
		INIT_ROT_X(rotation, cosa, sina);
	else if (axes == 1 || axes == 'y' || axes == 'Y')
		INIT_ROT_Y(rotation, cosa, sina);
	else if (axes == 2 || axes == 'z' || axes == 'Z')
		INIT_ROT_Z(rotation, cosa, sina);
	ft_memcpy((void*)m->m, matrix_mul(m, &rotation).m, sizeof(m->m));
}

t_matrix	projection_matrix(float fovy, float aspect, float near, float far)
{
	t_matrix	out;

	INIT_ZERO(out);
	out.m[5] = (float)(1.0f / tan(fovy / 2.0f));
	out.m[0] = out.m[5] / aspect;
	out.m[10] = -((far + near) / (far - near));
	out.m[11] = -1.0f;
	out.m[14] = -((2.0f * near * far) / (far - near));
	return (out);
}
