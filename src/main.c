/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 18:37:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"
#include "graphics.h"

int		main(int ac, char **av)
{
	t_window			win;

	if (ac != 2)
	{
		fprintf(stderr, "usage ./Scop file.obj\n");
		exit(1);
	}
	ft_bzero((void*)&win, sizeof(win));
	win.obj = obj_file_parser(av[1]);
	init_glut(ac, av, &win);
	glutMainLoop();
}
