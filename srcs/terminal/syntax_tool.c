/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:14:42 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 11:43:55 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"
#include "libft_printf.h"
#include "terminal.h"

/*
** Definie l'index de la chaine a la derniere quote
** Return [char] 0 - Success
** Return [char] Failed
*/

char	pass_quotes(char *str, int *index)
{
	int		i;
	char	quote;

	i = *index;
	quote = str[i];
	i++;
	while (str[i] && !(str[i] == quote && str[i - 1] != '\\'))
		i++;
	if (!str[i])
		return (quote);
	*index = i;
	return (0);
}

/*
 ** Definie l'index de le chaine en passant tous les blanks
 ** Return [void]
*/

void	pass_blank(char *str, int *index)
{
	int i;

	i = *index;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	*index = i;
}
