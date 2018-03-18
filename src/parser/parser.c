/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:12 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/19 00:29:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

static char		*g_names[5] = {
	"v ",
	"vt ",
	"vn ",
	"f ",
	NULL
};

static t_list		(*g_functions[5])(char **, int *, char *) = {
	face_elment_parser,
	face_elment_parser,
	face_elment_parser,
	face_parser,
	NULL
};

t_list				*face_parser(char **lines, int *i, char *prefix)
{
	// TODO: FORMAT LINE that supports 15/34/234 //234 //234
	t_list		*vertices;
	t_vertex	v;
	char		format_line[20];

	ft_bzero((void*)&(format_line[0]), 20);
	ft_strncat(&(format_line[0]), prefix, 20);
	ft_strncat(&(format_line[0]), "%9lf %9lf %9lf", 20);
	vertices = NULL;
	while (lines[++(*i)] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		sscanf(lines[*i], &(format_line[0]), &(v.x), &(v.y), &(v.z));
		ft_lstadd(&vertices, ft_lstnew((void*)&v, sizeof(t_vertex)));
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
	ft_strncat(&(format_line[0]), "%9lf %9lf %9lf", 20);
	vertices = NULL;
	while (lines[++(*i)] && !ft_strncmp(lines[(*i)], prefix, ft_strlen(prefix)))
	{
		sscanf(lines[*i], &(format_line[0]), &(v.x), &(v.y), &(v.z));
		ft_lstadd(&vertices, ft_lstnew((void*)&v, sizeof(t_vertex)));
	}
	return (vertices);
}

t_parsed_object		*obj_parser(char *file_contents)
{
	char		**lines;
	int			i;
	int			j;

	lines = ft_strsplit(file_contents, '\n');
	i = 0;
	while (lines[i])
	{
		j = -1;
		while (g_names[++j])
			if (!ft_strncmp(lines[i], g_names[j], ft_strlen(g_names[j])))
			// TODO: pass pointer to required vertex array
	}
}

t_parsed_object		*obj_file_parser(char *filename)
{
	char				*buf;
	t_parsed_object		*obj;

	buf = read_file_to_string(filename);
	obj = obj_parser(buf);
	ft_memdel((void**)&buf);
}
