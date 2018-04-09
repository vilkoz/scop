/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:12 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/09 14:10:52 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "libft.h"
#include "parser/reader.h"
#include "parser/parser.h"
#include "parser_private.h"
#include "progress_visualizer.h"

static char			*g_names[6] = {
	"v ",
	"vt ",
	"vn ",
	"f ",
	"mtllib ",
	NULL
};

static t_vector		*(*g_functions[6])(char **, int *, char *, void *) = {
	face_element_parser,
	face_element_parser,
	face_element_parser,
	face_parser,
	material_parser,
	NULL
};

static size_t		g_array_offsets[6] = {
	offsetof(struct s_parsed_object, v),
	offsetof(struct s_parsed_object, vt),
	offsetof(struct s_parsed_object, vn),
	offsetof(struct s_parsed_object, f),
	offsetof(struct s_parsed_object, mat),
	0
};

static t_vector		*face_element_parser(char **lines, int *i, char *prefix,
		void *obj)
{
	t_vector	*vertices;
	t_vertex	v;
	char		format_line[20];

	ft_bzero((void*)&(format_line[0]), 20);
	ft_strncat(&(format_line[0]), prefix, 20);
	ft_strncat(&(format_line[0]), "%9f %9f %9f", 20);
	vertices = obj ? (t_vector*)obj : vector_new(0, 0, sizeof(t_vertex));
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		sscanf(lines[*i], &(format_line[0]), &(v.x), &(v.y), &(v.z));
		VECTOR_ADD(vertices, &v);
		++(*i);
		update_visualizer(i);
	}
	vector_set_ready(vertices);
	return (vertices);
}

static void			call_function_by_index(char **lines, int *i, int j,
						t_parsed_object *obj)
{
	t_vector			*tmp;
	t_vector			**array_offset;

	array_offset = (t_vector**)((char*)obj + g_array_offsets[j]);
	tmp = g_functions[j](lines, i, g_names[j], j == 4 ? (void*)obj :
			(void*)*array_offset);
	*array_offset = tmp;
}

t_parsed_object		*obj_parser(char *file_contents, char *filename)
{
	char				**lines;
	int					i;
	int					j;
	t_parsed_object		*obj;

	obj = ft_memalloc(sizeof(t_parsed_object));
	obj->filename = filename;
	lines = ft_strsplit(file_contents, '\n');
	init_visualizer(lines, 0, &i);
	i = 0;
	while (lines[i])
	{
		j = -1;
		while (g_names[++j])
			if (!ft_strncmp(lines[i], g_names[j], ft_strlen(g_names[j])))
			{
				call_function_by_index(lines, &i, j, obj);
				break ;
			}
		if (g_names[j] == NULL)
			i++;
	}
	ft_del_string_array(lines);
	close_visualizer();
	return (obj);
}

static int			check_parsed_sizes(t_parsed_object *obj)
{
	if (obj->v == NULL || obj->v->size == 0)
	{
		fprintf(stderr, "no vertices found in file!\n");
		return (-1);
	}
	puts(" readed vectors sizes:");
	printf("  vertices: %zu\n", obj->v->size);
	if (obj->vn)
		printf("  normals: %zu\n", obj->vn->size);
	if (obj->vt)
		printf("  textures: %zu\n", obj->vt->size);
	puts(" readed indices vectors sizes:");
	printf("  vertices: %zu\n", obj->f->v->size);
	if (obj->f->n)
		printf("  normals: %zu\n", obj->f->n->size);
	if (obj->f->t)
		printf("  textures: %zu\n", obj->f->t->size);
	puts(" parsed object inited, starting flattening");
	return (0);
}

t_parsed_object		*obj_file_parser(char *filename)
{
	char				*buf;
	t_parsed_object		*obj;

	if ((buf = read_file_to_string(filename)) == NULL)
		return (NULL);
	obj = obj_parser(buf, filename);
	if (check_parsed_sizes(obj))
		return (NULL);
	obj = flatten_vectors(obj);
	puts(" flattened vectors sizes:");
	vector_set_ready(obj->v);
	printf("  vertices: %zu\n", obj->v->size / 3);
	if (obj->vn)
	{
		vector_set_ready(obj->vn);
		printf("  normals: %zu\n", obj->vn->size / 3);
	}
	if (obj->vt)
	{
		vector_set_ready(obj->vt);
		printf("  textures: %zu\n", obj->vt->size / 2);
	}
	ft_memdel((void**)&buf);
	return (obj);
}
