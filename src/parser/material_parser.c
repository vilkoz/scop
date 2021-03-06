/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 14:09:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/12 22:19:31 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"
#include "parser/reader.h"
#include "material_parser_private.h"
#include "bmp_loader/bmp_loader.h"

static char		*g_prefixes[6] = {
	"Ka ",
	"Kd ",
	"Ks ",
	"Ns ",
	"Tex ",
	NULL
};

static size_t	g_sizes[6] = {
	sizeof(t_vertex),
	sizeof(t_vertex),
	sizeof(t_vertex),
	sizeof(float),
	sizeof(void*),
	0
};

static size_t	g_offsets[6] = {
	offsetof(struct s_material, ka),
	offsetof(struct s_material, kd),
	offsetof(struct s_material, ks),
	offsetof(struct s_material, ns),
	offsetof(struct s_material, tex),
	0
};

static void		*(*g_callbacks[6])(char *line, char *prefix, char *file) = {
	parse_vertex,
	parse_vertex,
	parse_vertex,
	parse_float,
	load_texture,
	NULL
};

char			*get_relative_path(char *obj_name, char *mtl_name)
{
	size_t		path_size;
	char		*path;
	char		*last_slash;

	if ((last_slash = ft_strrchr(obj_name, '/')) == NULL)
		return (ft_strdup(mtl_name));
	path_size = last_slash - obj_name + 1;
	path = ft_strnew(path_size + 256);
	ft_strncpy(path, obj_name, path_size);
	ft_strncat(path, mtl_name, path_size + 256);
	return (path);
}

void			use_callback(t_material *m, char *line, int callback_index,
					char *current_filename)
{
	void		*m_field;
	void		*ret;

	m_field = (void*)m + g_offsets[callback_index];
	ret = g_callbacks[callback_index](line, g_prefixes[callback_index],
			current_filename);
	if (ret == NULL)
		return ;
	ft_memcpy(m_field, ret, g_sizes[callback_index]);
	ft_memdel(&ret);
}

void			parse_material_file(t_material *m, char **lines,
					char *current_filename)
{
	int		i;
	int		j;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (g_prefixes[++j])
		{
			if (!ft_strncmp(lines[i], g_prefixes[j], ft_strlen(g_prefixes[j])))
				use_callback(m, lines[i], j, current_filename);
		}
	}
	ft_del_string_array(lines);
}

t_vector		*material_parser(char **lines, int *i, char *prefix, void *obj)
{
	t_material		*m;
	char			*buf;
	char			filename[256];
	char			*relative_filename;

	(void)prefix;
	m = ft_memalloc(sizeof(t_material));
	ft_bzero((void*)&(filename[0]), 256);
	sscanf(lines[*i], "mtllib %s", &(filename[0]));
	relative_filename = get_relative_path(((t_parsed_object*)obj)->filename,
			&(filename[0]));
	(*i)++;
	buf = read_file_to_string(relative_filename);
	if (buf == NULL)
	{
		ft_memdel((void**)&m);
		ft_strdel(&relative_filename);
		return (NULL);
	}
	parse_material_file(m, ft_strsplit(buf, '\n'),
			((t_parsed_object*)obj)->filename);
	printf(" parsed material file %s\n", relative_filename);
	ft_strdel(&relative_filename);
	ft_strdel(&buf);
	return ((t_vector*)m);
}
