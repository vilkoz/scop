/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 14:09:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 16:44:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"
#include "parser/reader.h"
#include "material_parser_private.h"

static char		*g_prefixes[5] = {
	"Ka ",
	"Kd ",
	"Ks ",
	"Ns ",
	NULL
};

static size_t	g_sizes[5] = {
	sizeof(t_vertex),
	sizeof(t_vertex),
	sizeof(t_vertex),
	sizeof(float),
	0
};

static size_t	g_offsets[5] = {
	offsetof(struct s_material, ka),
	offsetof(struct s_material, kd),
	offsetof(struct s_material, ks),
	offsetof(struct s_material, ns),
	0
};

static void		*(*g_callbacks[5])(char *line, char *prefix) = {
	parse_vertex,
	parse_vertex,
	parse_vertex,
	parse_float,
	NULL
};

void			*parse_vertex(char *line, char *prefix)
{
	t_vertex	*v;
	char		format_string[64];

	v = ft_memalloc(sizeof(t_vertex));
	ft_bzero((void*)&(format_string[0]), 64);
	ft_strncat(&(format_string[0]), prefix, 64);
	ft_strncat(&(format_string[0]), " %f %f %f", 64);
	sscanf(line, &(format_string[0]), &(v->x), &(v->y), &(v->z));
	return ((void*)v);
}

void			*parse_float(char *line, char *prefix)
{
	float		*v;
	char		format_string[64];

	v = ft_memalloc(sizeof(float));
	ft_bzero((void*)&(format_string[0]), 64);
	ft_strncat(&(format_string[0]), prefix, 64);
	ft_strncat(&(format_string[0]), " %f", 64);
	sscanf(line, &(format_string[0]), v);
	return ((void*)v);
}

void			use_callback(t_material *m, char *line, int callback_index)
{
	void		*m_field;
	void		*ret;

	m_field = (void*)m + g_offsets[callback_index];
	ret = g_callbacks[callback_index](line, g_prefixes[callback_index]);
	ft_memcpy(m_field, ret, g_sizes[callback_index]);
	ft_memdel(&ret);
}

void			parse_material_file(t_material *m, char **lines)
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
				use_callback(m, lines[i], j);
		}
	}
}

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

t_vector		*material_parser(char **lines, int *i, char *prefix, void *obj)
{
	t_material		*m;
	char			*buf;
	char			filename[256];
	char			*relative_filename;

	(void)prefix;
	m = ft_memalloc(sizeof(t_material));
	ft_bzero((void*)&(filename[0]), 256);
	sscanf(lines[*i],"mtllib %s",&(filename[0]));
	relative_filename = get_relative_path(((t_parsed_object*)obj)->filename,
			&(filename[0]));
	(*i)++;
	buf = read_file_to_string(relative_filename);
	ft_strdel(&relative_filename);
	if (buf == NULL)
	{
		ft_memdel((void**)&m);
		return (NULL);
	}
	parse_material_file(m, ft_strsplit(buf, '\n'));
	return ((t_vector*)m);
}
