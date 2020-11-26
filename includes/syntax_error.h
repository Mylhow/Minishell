/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:48:04 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/26 16:08:36 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERRO_H
# define SYNTAX_ERROR_H

# define TO_EXECUTE 0
# define MALLOC_ERROR 1
# define NEW_LINE 2
# define NEW_COMMAND 3
# define MALLOC

//!DELETE
#include "libft_printf.h"

//SYNTAX_TOOLS_C
char	pass_quotes(char *str, int *index);
void	pass_blank(char *str, int *index);
char	print_syntax_err(void);

//SYNTAX_ERROR_C
char	syntax_error(char *input);

#endif
