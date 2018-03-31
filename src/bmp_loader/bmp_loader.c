/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 17:08:35 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 18:07:15 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_loader/bmp_loader.h"
#include "libft.h"
#include <stdio.h>
#include <stddef.h>

void		*bmp_loader(char *path)
{
	t_bmp_data		*b;
	FILE			*f;

	b = ft_memalloc(sizeof(t_bmp_data));
	f = fopen(path, "rb");
	if (!f)
	{
		perror(path);
		return (NULL);
	}
	if (fread((void*)&(b->header[0]), 1, 54, f) != 54 || b->header[0] != 'B'
		|| b->header[1] != 'M')
	{
		fprintf(stderr, "bmp_loader: wrong bmp file format: %s\n", path);
		return (NULL);
	}
	if ((b->data_pos = *(uint*)&(b->header[0xA])) == 0)
		b->data_pos = 54;
	b->w = *(uint*)&(b->header[0x12]);
	b->h = *(uint*)&(b->header[0x16]);
	if ((b->image_size = *(uint*)&(b->header[0x22])) == 0)
		b->image_size = b->w * b->h * 3;
	b->data = ft_memalloc(b->image_size);
	fread((void*)b->data, 1, b->image_size, f);
	fclose(f);
	return (b);
}
