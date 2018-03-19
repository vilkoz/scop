/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:12 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 00:11:04 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "libft.h"
#include "parser/parser.h"

static char		*g_names[5] = {
	"v ",
	"vt ",
	"vn ",
	"f ",
	NULL
};

static t_list		*(*g_functions[5])(char **, int *, char *) = {
	face_elment_parser,
	face_elment_parser,
	face_elment_parser,
	face_parser,
	NULL
};

static size_t	g_array_offsets[5] = {
	offsetof(struct s_parsed_object, v),
	offsetof(struct s_parsed_object, vt),
	offsetof(struct s_parsed_object, vn),
	offsetof(struct s_parsed_object, f),
	0
};

static size_t	g_num_offsets[5] = {
	offsetof(struct s_parsed_object, num_v),
	offsetof(struct s_parsed_object, num_vt),
	offsetof(struct s_parsed_object, num_vn),
	offsetof(struct s_parsed_object, num_f),
	0
};

char *read_file_to_string(char *filename)
{
	char		*buffer;
	long int	length;
	FILE		*f;

	buffer = NULL;
	f = fopen(filename, "rb");
	if (!f)
	{
		perror(filename);
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = ft_strnew(length);
	if (buffer)
		fread(buffer, 1, length, f);
	fclose(f);
	return (buffer);
}

t_list				*parse_face_line(char *line)
{
	t_list		*face;
	size_t		len;
	size_t		i;
	int			num;

	face = NULL;
	if ((len = ft_strlen(line)) == 0 || len < 5)
	{
		fprintf(stderr, "wrong face line: %s!\n", line);
		return (NULL);
	}
	i = 1;
	while (i < len && line[i] == ' ')
		i++;
	while (i < len)
	{
		sscanf(line + i, "%d ", &num);
		ft_lstadd(&face, ft_lstnew((void*)&num, sizeof(int)));
		while (ft_isdigit(line[i]))
			i++;
		while (i < len && line[i] == ' ')
			i++;
	}
	return (face);
}

t_list				*face_parser(char **lines, int *i, char *prefix)
{
	// TODO: FORMAT LINE that supports 15/34/234 //234 //234
	t_list		*vertices;
	t_list		*parsed_line;

	vertices = NULL;
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		parsed_line = parse_face_line(lines[*i]);
		ft_lstadd(&vertices, ft_lstnew((void*)&parsed_line, sizeof(t_list*)));
		++(*i);
	}
	return (vertices);
}

t_list				*face_elment_parser(char **lines, int *i, char *prefix)
{
	t_list		*vertices;
	t_vertex	v;
	char		format_line[20];

	ft_bzero((void*)&(format_line[0]), 20);
	ft_strncat(&(format_line[0]), prefix, 20);
	ft_strncat(&(format_line[0]), "%9f %9f %9f", 20);
	vertices = NULL;
	while (lines[*i] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		sscanf(lines[*i], &(format_line[0]), &(v.x), &(v.y), &(v.z));
		ft_lstadd(&vertices, ft_lstnew((void*)&v, sizeof(t_vertex)));
		++(*i);
	}
	return (vertices);
}

void				call_function_by_index(char **lines, int *i, int j,
						t_parsed_object *obj)
{
	t_list				*tmp;
	unsigned int		*num_offset;
	t_vertex			***array_offset;

	tmp = g_functions[j](lines, i, g_names[j]);
	tmp = ft_lst_rev(tmp);
	num_offset = (unsigned int*)(((char*)obj) + g_num_offsets[j]);
	*num_offset = (unsigned int)ft_lst_size(tmp);
	array_offset = (t_vertex***)((char*)obj + g_array_offsets[j]);
	if (j != 3)
	{
		*array_offset = (t_vertex**)ft_lst_to_array(tmp);
		ft_lstdel(&tmp, NULL);
	}
	else
		*array_offset = (t_vertex**)tmp;
}

t_parsed_object		*obj_parser(char *file_contents)
{
	char				**lines;
	int					i;
	int					j;
	t_parsed_object		*obj;

	obj = ft_memalloc(sizeof(t_parsed_object));
	lines = ft_strsplit(file_contents, '\n');
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
		(g_names[j] == NULL) ? i++ : 0;
	}
	return (obj);
}

t_parsed_object		*obj_file_parser(char *filename)
{
	char				*buf;
	t_parsed_object		*obj;

	buf = read_file_to_string(filename);
	obj = obj_parser(buf);
	ft_memdel((void**)&buf);

	printf("obj->num_v = %u\n", obj->num_v);
	printf("obj->num_vt = %u\n", obj->num_vt);
	printf("obj->num_vn = %u\n", obj->num_vn);
	printf("obj->num_f = %u\n", obj->num_f);
#define PRINT_VERTEX(v) (v)->x, (v)->y, (v)->z
	int i = -1;
	while((obj->v)[++i]) printf("obj->v[%d] = %f, %f, %f\n", i, PRINT_VERTEX(obj->v[i]));
	t_list *tmp_i = obj->f;
	t_list *tmp_j = NULL;
	while (tmp_i)
	{
		tmp_j = (t_list*)(tmp_i->content);
		while (tmp_j)
		{
			printf(" %ls ", (int*)tmp_j->content);
			tmp_j = tmp_j->next;
		}
		tmp_i = tmp_i->next;
	}
	return (obj);
}
