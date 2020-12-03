/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:48:04 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/30 11:28:19 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_H
# define SYNTAX_ERROR_H

# define TO_EXECUTE 0
# define MALLOC_ERROR 1
# define NEW_LINE 2
# define NEW_COMMAND 3
# define NCMD_SYNTAX_ERROR 4

# define WORD 0
# define OPERAT 1
# define PARENTH 2
# define REDIRECT 3

//SYNTAX_TOOLS_C
char	pass_quotes(char *str, int *index);
void	pass_blank(char *str, int *index);

//SYNTAX_ERROR_C
short	syntax_error(char *input, int flagantislash);

#endif
