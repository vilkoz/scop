/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser_private.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:49:47 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 15:50:04 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_PARSER_PRIVATE_H
# define MATERIAL_PARSER_PRIVATE_H


void			*parse_vertex(char *line, char *prefix);
void			*parse_float(char *line, char *prefix);

#endif
