/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 23:59:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"
#include "graphics.h"
#include "libft.h"
#include "object.h"

static t_vector	*parse_objects(int ac, char **av)
{
	t_vector		*v;
	t_parsed_object	*tmp;
	int				i;

	v = vector_new(0, 0, sizeof(t_parsed_object*));
	i = 0;
	while (++i < ac)
	{
		if ((tmp = obj_file_parser(av[i])) != NULL)
		{
			printf("tmp == %p\n", tmp);
			VECTOR_ADD(v, &tmp);
		}
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
		VECTOR_GET_TO(tmp, parsed_objects, i);
		printf("tmp == %p\n", *tmp);
		obj = new_object(*tmp);
		VECTOR_ADD(v, &obj);
	}
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
	/* win.obj = obj_file_parser(av[1]); */
	fprintf(stderr, "start parsing\n");
	win.obj = parse_objects(ac, av);
	if (win.obj->size == 0)
		return (0);
	fprintf(stderr, "end parsing\n");
	puts("glut not inited");
	init_glut(ac, av, &win);
	fprintf(stderr, "glut inited\n");
	win.obj = init_objects(win.obj);
	fprintf(stderr, "objs inited\n");
	glutMainLoop();
}
