/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:17:30 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/21 19:25:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "libft.h"

char				*read_file_to_string(char *filename)
{
	char		*buffer;
	long int	length;
	FILE		*f;

	buffer = NULL;
	f = fopen(filename, "rb");
	if (!f)
	{
		perror(filename);
		return (NULL);
	}
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = ft_strnew(length);
	if (buffer)
		fread(buffer, 1, length, f);
	fclose(f);
	return (buffer);
}
