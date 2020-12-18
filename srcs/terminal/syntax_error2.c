/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:10:48 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 13:25:26 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_string.h"
#include "syntax_error.h"

/*
** Check le contenu des parentheses
** Return [char] 1 - Error Malloc
** Return [char] * - Call Syntax error
*/

static char	recursion_parenth(char *input, int length)
{
	int		i;
	char	*str_parenth;
	char	return_value;

	if (!(str_parenth = wrmalloc((length + 1) * sizeof(char))))
		return (MALLOC_ERROR);
	ft_strlcpy(str_parenth, input, length + 1);
	i = length - 2;
	while (i > 0 && (str_parenth[i] == ' ' || str_parenth[i] == '\t'))
		i--;
	str_parenth[length - 1] = (str_parenth[i] != ';') ? ';' : '\0';
	return_value = syntax_error(str_parenth, 0);
	wrfree(str_parenth);
	return (return_value);
}

/*
** Check les parenthese ouverture et fermeture
** Return [char] 3 - Call syntax error
** Return [char] 2 - Call new line
** Return [char] * - Check le contenu des parentheses
*/

char		syntax_parenth(char *input, int type, int *index, int i)
{
	int		nbr_parenth;

	if (type == WORD || type == REDIRECT)
		return (NCMD_SYNTAX_ERROR);
	nbr_parenth = 1;
	while (input[i] && nbr_parenth)
	{
		if (input[i] == '\\')
			i++;
		else if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NCMD_SYNTAX_ERROR);
		}
		else if (input[i] == '(' || input[i] == ')')
			nbr_parenth += (input[i] == '(') ? 1 : -1;
		i += (nbr_parenth && input[i]) ? 1 : 0;
	}
	if (nbr_parenth)
	{
		return ((syntax_error(input + 1, 0) == NCMD_SYNTAX_ERROR)
						? NCMD_SYNTAX_ERROR : NLINE_COMMA);
	}
	*index += i + 1;
	return (recursion_parenth(input + 1, i));
}

int			is_end_escaped(char *input)
{
	int		i;

	i = 0;
	while (input[i])
		i++;
	if (!i)
		return (0);
	i--;
	return (is_escaped(input, i));
}
