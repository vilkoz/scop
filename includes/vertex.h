/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 00:39:41 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/22 00:53:23 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include <math.h>

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
}					t_vertex;

# define NEW_VERTEX(x, y, z) (t_vertex){(x), (y), (z)}

t_vertex			vertex_new(float *a);
t_vertex			vertex_sub(t_vertex v1, t_vertex v2);
t_vertex			vertex_norm(t_vertex v);
t_vertex			vertex_cross(t_vertex v1, t_vertex v2);

#endif
