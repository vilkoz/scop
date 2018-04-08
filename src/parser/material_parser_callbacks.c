/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser_callbacks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:10:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 15:14:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "vertex.h"
#include "bmp_loader/bmp_loader.h"
#include "material_parser_callbacks_private.h"

void			*load_texture(char *line, char *prefix, char *current_filename)
{
	void		**res;
	char		tex_filename[256];
	char		*tex_path;

	(void)prefix;
	ft_bzero((void*)&(tex_filename[0]), 256);
	if (sscanf(line, "Tex %255s", &(tex_filename[0])) != 1)
	{
		fprintf(stderr, "load_texture: wrong texture name in line: %s\n", &(tex_filename[0]));
		return (NULL);
	}
	tex_path = get_relative_path(current_filename, &(tex_filename[0]));
	res = ft_memalloc(sizeof(void*));
	*res = bmp_loader(tex_path);
	if (res == NULL)
	{
		fprintf(stderr, "load_bmp: failed loading texture from: %s\n", tex_path);
		return (NULL);
	}
	printf("loaded texture: %s\n", tex_path);
	ft_strdel(&tex_path);
	return (res);
}

void			*parse_vertex(char *line, char *prefix, char *current_filename)
{
	t_vertex	*v;
	char		format_string[64];

	(void)current_filename;
	v = ft_memalloc(sizeof(t_vertex));
	ft_bzero((void*)&(format_string[0]), 64);
	ft_strncat(&(format_string[0]), prefix, 64);
	ft_strncat(&(format_string[0]), " %f %f %f", 64);
	sscanf(line, &(format_string[0]), &(v->x), &(v->y), &(v->z));
	return ((void*)v);
}

void			*parse_float(char *line, char *prefix, char *current_filename)
{
	float		*v;
	char		format_string[64];

	(void)current_filename;
	v = ft_memalloc(sizeof(float));
	ft_bzero((void*)&(format_string[0]), 64);
	ft_strncat(&(format_string[0]), prefix, 64);
	ft_strncat(&(format_string[0]), " %f", 64);
	sscanf(line, &(format_string[0]), v);
	return ((void*)v);
}
