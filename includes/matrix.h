/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 01:04:57 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 02:19:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct		s_matrix
{
	float			m[16];
}					t_matrix;

# define ZERO_M(m) (typeof(m)){{0}}
# define INIT_ZERO(m) m = ZERO_M(m)
# define EYE_M(m) (typeof(m)){{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}}
# define INIT_EYE(m) m = EYE_M(m)
# define ROT_M_X(c, s) {{1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1}}
# define INIT_ROT_X(m, c, s) m = (typeof(m))ROT_M_X(c, s)
# define ROT_M_Y(c, s) {{c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1}}
# define INIT_ROT_Y(m, c, s) m = (typeof(m))ROT_M_Y(c, s)
# define ROT_M_Z(c, s) {{c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}}
# define INIT_ROT_Z(m, c, s) m = (typeof(m))ROT_M_Z(c, s)

t_matrix			matrix_mul(t_matrix *m1, t_matrix *m2);
t_matrix			projection_matrix(float fovy, float aspect,
						float near, float far);
void				rotate_matrix(t_matrix *m, float angle, char axes);
void				translate_matrix(t_matrix *m, float x, float y, float z);
void				scale_matrix(t_matrix *m, float x, float y, float z);

#endif
