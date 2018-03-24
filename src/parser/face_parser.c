/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:24:52 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/24 18:07:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "face_parser_private.h"
#include <stdio.h>

static char		*g_format_lines[9] = {
	"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
	"f %d/%d/%d %d/%d/%d %d/%d/%d",
	"f %d//%d %d//%d %d//%d %d//%d",
	"f %d//%d %d//%d %d//%d",
	"f %d/%d/ %d/%d/ %d/%d/ %d/%d/",
	"f %d/%d/ %d/%d/ %d/%d/",
	"f %d %d %d %d",
	"f %d %d %d",
	NULL
};

static int		g_valid_return[9] = {
	12,
	9,
	8,
	6,
	8,
	6,
	4,
	3,
	-1
};

static int		g_indexes_align[9][12] = {
	{0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2},
	{0, 1, 2, 0, 1, 2, 0, 1, 2, -1, -1, -1},
	{0, 1, 0, 1, 0, 1, 0, 1, -1, -1, -1, -1},
	{0, 1, 0, 1, 0, 1, -1, -1, -1, -1, -1, -1},
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
	/* printf("indexes: "); */
	/* for (int j = 0; j < 12; j++) { */
	/* 	printf(" %d", ind[j]); */
	/* } */
	/* puts(""); */
	i = -1;
	while (++i < 12)
	{
		if ((vector_index = g_indexes_align[array_number][i]) >= 0)
			VECTOR_ADD(vectors[vector_index], &(ind[i]));
	}
	if (g_valid_return[array_number] % 3 == 0)
	{
		i = -1;
		while (++i < 3)
			if ((vector_index = g_indexes_align[array_number][i]) >= 0)
				VECTOR_ADD(vectors[vector_index], &(ind[i]));
	}
	/* printf("v: "); */ 
	/* int *gopa_super_random; */ 
	/* for (size_t randomw_iDdsD = 0; randomw_iDdsD < indexes->v->size; randomw_iDdsD++) { */ 
	/* 	VECTOR_GET_TO(gopa_super_random, indexes->v, randomw_iDdsD); */
	/* 	printf(" %d ", *gopa_super_random); */ 
	/* } */ 
	/* puts(""); */ 
	/* printf("n: "); */ 
	/* for (size_t randomw_iDdsD = 0; randomw_iDdsD < indexes->n->size; randomw_iDdsD++) { */ 
	/* 	VECTOR_GET_TO(gopa_super_random, indexes->n, randomw_iDdsD); */
	/* 	printf(" %d ", *gopa_super_random); */ 
	/* } */ 
	/* puts(""); */ 
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
	while (++i < 8)
	{
		res = sscanf(line, g_format_lines[i], &(ind[0]), &(ind[1]), &(ind[2]),
				&(ind[3]), &(ind[4]), &(ind[5]), &(ind[6]), &(ind[7]),
				&(ind[8]), &(ind[9]), &(ind[10]), &(ind[11]), &(ind[12]));
		if (res != g_valid_return[i] && i == 7)
				throw_face_parse_error(line);
		else if (res == g_valid_return[i])
			break ;
	}
	printf("parsed with |%s|\n", g_format_lines[i]);
	insert_to_indexes_with_align(i, &(ind[0]), indexes);
}

t_vector				*face_parser(char **lines, int *i, char *prefix)
{
	t_indexes		*indexes;

	indexes = ft_memalloc(sizeof(t_indexes));
	indexes->v = vector_new(NULL, 0, sizeof(int));
	indexes->t = vector_new(NULL, 0, sizeof(int));
	indexes->n = vector_new(NULL, 0, sizeof(int));
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		parse_face_line(lines[*i], indexes);
		++(*i);
	}
	vector_set_ready(indexes->v);
	vector_set_ready(indexes->t);
	vector_set_ready(indexes->n);
	return ((t_vector*)indexes);
}
