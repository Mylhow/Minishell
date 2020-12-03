/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:10:48 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/02 15:15:51 by abourbou         ###   ########lyon.fr   */
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

char		syntax_parenth(char *input, int type, int *index)
{
	int		i;
	int		nbr_parenth;

	if (type == WORD || type == REDIRECT)
		return (NCMD_SYNTAX_ERROR);
	i = 1;
	nbr_parenth = 1;
	while (input[i] && nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NCMD_SYNTAX_ERROR);
		}
		else if (input[i] == '(')
			nbr_parenth++;
		else if (input[i] == ')')
			nbr_parenth--;
		i += (nbr_parenth) ? 1 : 0;
	}
	if (nbr_parenth)
		return (NLINE_COMMA);
	*index += i + 1;
	return (recursion_parenth(input + 1, i));
}
