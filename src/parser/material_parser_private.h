/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser_private.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:49:47 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/12 22:18:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_PARSER_PRIVATE_H
# define MATERIAL_PARSER_PRIVATE_H

void			*parse_vertex(char *line, char *prefix, char *file);
void			*parse_float(char *line, char *prefix, char *file);
void			*load_texture(char *line, char *prefix, char *file);

#endif
