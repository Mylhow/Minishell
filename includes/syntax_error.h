/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:48:04 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 14:03:22 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_H
# define SYNTAX_ERROR_H

# include "sh_utils.h"

# define TO_EXECUTE 0
# define MALLOC_ERROR 1
# define NEW_LINE 2
# define NEW_COMMAND 3
# define NCMD_SYNTAX_ERROR 4
# define NLINE_COMMA 5

# define WORD 0
# define OPERAT 1
# define PARENTH 2
# define REDIRECT 3

char	pass_quotes(char *str, int *index);
void	pass_blank(char *str, int *index);

short	syntax_error(char *input, int flagantislash);

char	syntax_parenth(char *input, int type, int *index, int i);
int		is_end_escaped(char *input);
int		check_empty_line(char *input);
int		is_operator(char *input, int *i);

#endif
