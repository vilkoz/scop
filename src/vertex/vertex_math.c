/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 00:41:39 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/23 00:11:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex.h"

t_vertex		vertex_new(float *a)
{
	return (NEW_VERTEX(a[0], a[1], a[2]));
}

t_vertex		vertex_sub(t_vertex v1, t_vertex v2)
{
	return (NEW_VERTEX(v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z));
}

t_vertex		vertex_norm(t_vertex v)
{
	float	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabs(len) > 0.0001)
		return (NEW_VERTEX(v.x / len, v.y / len, v.z / len));
	return (v);
}

t_vertex		vertex_cross(t_vertex v1, t_vertex v2)
{
	return (NEW_VERTEX(v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x));
}
