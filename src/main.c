/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 01:25:33 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"
#include "graphics.h"
#include "libft.h"
#include "object.h"
#include "skybox.h"

static t_vector	*parse_objects(int ac, char **av)
{
	t_vector		*v;
	t_parsed_object	*tmp;
	int				i;

	v = vector_new(0, 0, sizeof(t_parsed_object*));
	i = 0;
	while (++i < ac)
	{
		printf("parsing object #%i:\n", i);
		if ((tmp = obj_file_parser(av[i])) != NULL)
			VECTOR_ADD(v, &tmp);
		puts("");
	}
	vector_set_ready(v);
	return (v);
}

static t_vector	*init_objects(t_vector *parsed_objects)
{
	t_vector		*v;
	t_parsed_object	**tmp;
	t_object		*obj;
	int			i;

	v = vector_new(0, 0, sizeof(t_object*));
	i = -1;
	while (++i < (int)parsed_objects->size)
	{
		printf("initialize object #%i:\n", i);
		VECTOR_GET_TO(tmp, parsed_objects, i);
		obj = new_object(*tmp);
		VECTOR_ADD(v, &obj);
		puts("");
	}
	/* obj = new_skybox(); */
	/* VECTOR_ADD(v, &obj); */
	vector_delete(&parsed_objects, NULL);
	vector_set_ready(v);
	return (v);
}

int				main(int ac, char **av)
{
	t_window			win;

	if (ac < 2)
	{
		fprintf(stderr, "usage ./Scop file.obj ...\n");
		exit(1);
	}
	ft_bzero((void*)&win, sizeof(win));
	puts("-------------start parsing all objects--------------");
	puts("start parsing all objects");
	win.obj = parse_objects(ac, av);
	if (win.obj->size == 0)
		return (0);
	puts("-----------finished parsing all objects-------------");
	puts("------------------sdl initialization----------------");
	init_sdl(ac, av, &win);
	puts("----------------end sdl initialization--------------");
	puts("-------------start initialize all objects-----------");
	win.obj = init_objects(win.obj);
	puts("--------------end initialize all objects------------");
	sdl_main_loop(&win);
}
