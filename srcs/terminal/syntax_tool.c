/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:14:42 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 14:29:49 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"
#include "libft_printf.h"
#include "terminal.h"
#include "libft_string.h"

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
	if (quote == '\"')
	{
		while (str[i] && !(str[i] == quote && !is_escaped(str, i)))
			i++;
	}
	else
	{
		while (str[i] && str[i] != quote)
			i++;
	}
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

/*
** Check si la ligne est vide
** Return [int] 1 - Success
** Return [int] 0 - Failed
*/

int		check_empty_line(char *input)
{
	int i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (1);
	return (0);
}

int		is_operator(char *input, int *i)
{
	if (!ft_strncmp(">>", input + *i, 2)
			|| !ft_strncmp("&&", input + *i, 2)
			|| !ft_strncmp("||", input + *i, 2))
		return (1);
	return (0);
}
