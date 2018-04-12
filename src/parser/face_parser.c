/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:24:52 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/12 22:47:47 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "face_parser_private.h"
#include <stdio.h>

static char		*g_format_lines[6] = {
	"%d/%d/%d",
	"%d//%d",
	"%d/%d/",
	"%d/%d",
	"%d",
	NULL
};

static int		g_valid_return[6] = {
	3,
	2,
	2,
	2,
	1,
	0
};

static int		g_indexes_align[6][3] = {
	{VERTEX, TEXTURE, NORMAL},
	{VERTEX, NORMAL, SKIP},
	{VERTEX, TEXTURE, SKIP},
	{VERTEX, TEXTURE, SKIP},
	{VERTEX, SKIP, SKIP},
	{0, 0, 0},
};

void			vertex_insert_to_indexes_with_align(int array_number, int *ind,
					t_indexes *indexes)
{
	int					i;
	t_vector			*vectors[3];
	int					vector_index;

	vectors[VERTEX] = indexes->v;
	vectors[NORMAL] = indexes->n;
	vectors[TEXTURE] = indexes->t;
	i = -1;
	while (++i < 3)
	{
		if ((vector_index = g_indexes_align[array_number][i]) != SKIP)
			VECTOR_ADD(vectors[vector_index], &(ind[i]));
	}
}

int				detect_index(char *first_vertex)
{
	int			i;
	int			ret;
	int			tmp[3];

	i = -1;
	while (g_format_lines[++i])
	{
		ret = sscanf(first_vertex, g_format_lines[i], &(tmp[0]),
				&(tmp[1]), &(tmp[2]));
		if (ret == g_valid_return[i])
			break ;
		else if (i == sizeof(g_format_lines) / sizeof(g_format_lines[0]) - 1)
			THROW_FACE_PARSE_ERROR(first_vertex);
	}
	return (i);
}

void			insert_triangle(int array_number, char **triangle,
					t_indexes *indexes)
{
	int			i;
	int			ret;
	int			vertex[3];

	i = -1;
	while (++i < 3)
	{
		ft_bzero((void*)&(vertex[0]), 3 * sizeof(int));
		ret = sscanf(triangle[i], g_format_lines[array_number], &(vertex[0]),
				&(vertex[1]), &(vertex[2]));
		if (ret != g_valid_return[array_number])
			THROW_FACE_PARSE_ERROR(triangle[i]);
		vertex_insert_to_indexes_with_align(array_number, &(vertex[0]),
				indexes);
	}
}

void			parse_face_line(char *line, char **tokens, t_indexes *indexes)
{
	int				i;
	size_t			len;
	int				format_array_index;
	char			*triangle[3];

	if (tokens == NULL)
		THROW_FACE_PARSE_ERROR("NULL");
	len = 0;
	while (tokens[len] != NULL)
		len++;
	if (len < 4)
		THROW_FACE_PARSE_ERROR(line);
	format_array_index = detect_index(tokens[1]);
	i = 1;
	while (tokens[i] && tokens[i + 1] && tokens[i + 2])
	{
		triangle[0] = tokens[i];
		triangle[1] = tokens[i + 1];
		triangle[2] = tokens[i + 2];
		insert_triangle(format_array_index, &(triangle[0]), indexes);
		i += 2;
	}
	if ((len - 1) % 3 != 0)
		insert_triangle(format_array_index, ((char*[3]){tokens[len - 2],
					tokens[len - 1], tokens[1]}), indexes);
}

t_vector		*face_parser(char **lines, int *i, char *prefix,
							void *obj)
{
	t_indexes		*indexes;
	char			**tokens;

	indexes = (obj) ? (t_indexes*)obj : ft_memalloc(sizeof(t_indexes));
	if (!indexes->v)
		indexes->v = vector_new(NULL, 0, sizeof(int));
	if (!indexes->t)
		indexes->t = vector_new(NULL, 0, sizeof(int));
	if (!indexes->n)
		indexes->n = vector_new(NULL, 0, sizeof(int));
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		tokens = ft_strsplit(lines[*i], ' ');
		parse_face_line(lines[*i], tokens, indexes);
		ft_del_string_array(tokens);
		++(*i);
	}
	return ((t_vector*)indexes);
}
