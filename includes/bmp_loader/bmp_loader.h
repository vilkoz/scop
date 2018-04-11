/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 17:12:07 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/11 21:40:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_LOADER_H
# define BMP_LOADER_H

typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;

typedef struct		s_bmp_data
{
	t_uchar			header[54];
	t_uint			w;
	t_uint			h;
	t_uint			image_size;
	t_uchar			*data;
	t_uint			data_pos;
}					t_bmp_data;

void				*bmp_loader(char *path);

#endif
