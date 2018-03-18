/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:12 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/18 23:53:41 by vrybalko         ###   ########.fr       */
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

t_list				*v_parser(char **lines, int *i)
{
	t_list		*vertices;

	vertices = NULL;
	while (lines[++(*i)] && ft_strncmp(lines[(*i)], "v ", 2))
	{
	}
}

t_parsed_object		*obj_parser(char *file_contents)
{
	char		**lines;
	int			i;

	lines = ft_strsplit(file_contents, '\n');
	i = -1;
}

t_parsed_object		*obj_file_parser(char *filename)
{
	char				*buf;
	t_parsed_object		*obj;

	buf = read_file_to_string(filename);
	obj = obj_parser(buf);
	ft_memdel((void**)&buf);
}
