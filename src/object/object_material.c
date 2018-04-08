/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:23:55 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 14:38:31 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_loader/bmp_loader.h"
#include "object/object.h"
#include "libft.h"

static void		print_object_material_info(t_material *m)
{
	puts(" ---------------object material info----------------");
	printf(" ka: %f %f %f\n", m->ka.x, m->ka.y, m->ka.z);
	printf(" kd: %f %f %f\n", m->kd.x, m->kd.y, m->kd.z);
	printf(" ks: %f %f %f\n", m->ks.x, m->ks.y, m->ks.z);
	printf(" ns: %f\n", m->ns);
	puts(" ---------------------------------------------------");
}

static void		check_texture_error(void *tex, const char *default_tex)
{
	if (tex == NULL)
	{
		fprintf(stderr, "NO DEFAULT TEXTURE FILE FOUND %s\n", default_tex);
		exit(1);
	}
}

t_material		*init_object_material(t_material *p)
{
	t_material		*m;
	const char		*default_tex = "res/sky.bmp";

	if (p != NULL)
	{
		if (p->tex == NULL)
			p->tex = bmp_loader((char*)default_tex);
		check_texture_error(p->tex, default_tex);
		print_object_material_info(p);
		return (p);
	}
	m = ft_memalloc(sizeof(t_material));
	m->ka = NEW_VERTEX(0.1, 0.1, 0.1);
	m->kd = NEW_VERTEX(0.7, 0.7, 0.7);
	m->ks = NEW_VERTEX(0.1, 0.1, 0.1);
	m->ns = 50.f;
	m->tex = bmp_loader((char*)default_tex);
	check_texture_error(m->tex, default_tex);
	print_object_material_info(m);
	return (m);
}
