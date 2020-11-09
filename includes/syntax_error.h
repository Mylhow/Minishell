/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:48:04 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/09 09:15:35 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//SYNTAX_TOOLS_C
char	pass_quotes(char *str, int *index);
void	pass_blank(char *str, int *index);

//SYNTAX_ERROR_C
char	syntax_error(char *input);

#endif
