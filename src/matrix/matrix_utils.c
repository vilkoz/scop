/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 01:07:58 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 01:40:16 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix		matrix_mul(t_matrix *m1, t_matrix *m2)
{
	t_matrix		out;
	unsigned int	row;
	unsigned int	collumn;

	row = 0;
	while (row < 4)
	{
		collumn = 0;
		while (collumn < 4)
		{
			out.m[row * 4 + collumn] = 
				(m1->m[row * 4 + 0] * m2->m[collumn + 0 * 4]) + 
				(m1->m[row * 4 + 1] * m2->m[collumn + 1 * 4]) + 
				(m1->m[row * 4 + 2] * m2->m[collumn + 2 * 4]) + 
				(m1->m[row * 4 + 3] * m2->m[collumn + 3 * 4]);
			collumn++;
		}
		row++;
	}
	return (out);
}
