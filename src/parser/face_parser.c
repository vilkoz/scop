/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:24:52 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/25 01:26:42 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "face_parser_private.h"
#include <stdio.h>

static char		*g_format_lines[12] = {
	"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
	"f %d/%d/%d %d/%d/%d %d/%d/%d",
	"f %d//%d %d//%d %d//%d %d//%d",
	"f %d//%d %d//%d %d//%d",
	"f %d/%d/ %d/%d/ %d/%d/ %d/%d/",
	"f %d/%d/ %d/%d/ %d/%d/",
	"f %d/%d %d/%d %d/%d %d/%d",
	"f %d/%d %d/%d %d/%d",
	"f %d %d %d %d",
	"f %d %d %d",
	NULL
};

static int		g_valid_return[12] = {
	12,
	9,
	8,
	6,
	8,
	6,
	8,
	6,
	4,
	3,
	-1
};

static int		g_indexes_align[12][12] = {
	{0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2},
	{0, 1, 2, 0, 1, 2, 0, 1, 2, -1, -1, -1},
	{0, 1, 0, 1, 0, 1, 0, 1, -1, -1, -1, -1},
	{0, 1, 0, 1, 0, 1, -1, -1, -1, -1, -1, -1},
	{0, 2, 0, 2, 0, 2, 0, 2, -1, -1, -1, -1},
	{0, 2, 0, 2, 0, 2, -1, -1, -1, -1, -1, -1},
	{0, 2, 0, 2, 0, 2, 0, 2, -1, -1, -1, -1},
	{0, 2, 0, 2, 0, 2, -1, -1, -1, -1, -1, -1},
	{0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

void			throw_face_parse_error(char *line)
{
	fprintf(stderr, "wrong face line: %s!\n", line);
	exit(1);
}

void			insert_to_indexes_with_align(int array_number, int *ind,
					t_indexes *indexes)
{
	int					i;
	t_vector			*vectors[3];
	int					vector_index;

	vectors[0] = indexes->v;
	vectors[1] = indexes->n;
	vectors[2] = indexes->t;
	i = -1;
	while (++i < 12)
	{
		if ((vector_index = g_indexes_align[array_number][i]) >= 0)
			VECTOR_ADD(vectors[vector_index], &(ind[i]));
	}
	if (g_valid_return[array_number] % 4 != 0)
	{
		i = -1;
		while (++i < g_valid_return[array_number] / 3)
			if ((vector_index = g_indexes_align[array_number][i]) >= 0)
				VECTOR_ADD(vectors[vector_index], &(ind[i]));
	}
}

void			parse_face_line(char *line, t_indexes *indexes)
{
	size_t		len;
	int			i;
	int			res;
	int			ind[12];

	ft_bzero((void**)&(ind[0]), sizeof(int) * 3 * 4);
	if ((len = ft_strlen(line)) < 5)
		throw_face_parse_error(line);
	i = -1;
	while (++i < 11)
	{
		res = sscanf(line, g_format_lines[i], &(ind[0]), &(ind[1]), &(ind[2]),
				&(ind[3]), &(ind[4]), &(ind[5]), &(ind[6]), &(ind[7]),
				&(ind[8]), &(ind[9]), &(ind[10]), &(ind[11]), &(ind[12]));
		if (res != g_valid_return[i] && i == 10)
				throw_face_parse_error(line);
		else if (res == g_valid_return[i])
			break ;
	}
	insert_to_indexes_with_align(i, &(ind[0]), indexes);
}

t_vector				*face_parser(char **lines, int *i, char *prefix,
							void *obj)
{
	t_indexes		*indexes;

	indexes = (obj) ? (t_indexes*)obj : ft_memalloc(sizeof(t_indexes));
	if (!indexes->v)
		indexes->v = vector_new(NULL, 0, sizeof(int));
	if (!indexes->t)
		indexes->t = vector_new(NULL, 0, sizeof(int));
	if (!indexes->n)
		indexes->n = vector_new(NULL, 0, sizeof(int));
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		parse_face_line(lines[*i], indexes);
		++(*i);
	}
	/* vector_set_ready(indexes->v); */
	/* vector_set_ready(indexes->t); */
	/* vector_set_ready(indexes->n); */
	return ((t_vector*)indexes);
}
