/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:52:17 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/19 22:34:32 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser/parser.h"

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "usage ./Scop file.obj\n");
		exit(1);
	}
	obj_file_parser(av[1]);
}
