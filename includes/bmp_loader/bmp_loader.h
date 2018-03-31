/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 17:12:07 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 18:04:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_LOADER_H
# define BMP_LOADER_H

typedef unsigned char		uchar;
typedef unsigned int		uint;

typedef struct		s_bmp_data
{
	uchar			header[54];
	uint			w;
	uint			h;
	uint			image_size;
	uchar			*data;
	uint			data_pos;
}					t_bmp_data;

void				*bmp_loader(char *path);

#endif
