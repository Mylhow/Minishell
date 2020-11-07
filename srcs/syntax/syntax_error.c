/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:07:14 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/07 10:52:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_string.h"
#include "parsing.h"
char	recursion_parenth(char *input, int length)
{
	int		i;
	char	*str_parenth;
	char	return_value;

	if (!(str_parenth = wrmalloc((length + 1) * sizeof(char))))
		return (1);
	ft_strlcpy(str_parenth, input, length + 1);
	i = length - 2;
	while (i > 0 && (str_parenth[i] == ' ' || str_parenth[i] == '\t'))
		i--;
	str_parenth[length - 1] = (str_parenth[i] != ';') ? ';' : '\0';
	return_value = syntax_error(str_parenth);
	wrfree(str_parenth);
	return(return_value);
}

char	syntax_parenth(char *input, int type, int *index)
{
	char	return_value;
	int		i;
	int		nbr_parenth;

	if (type == 0)
		return ('(');
	i = 1;
	nbr_parenth = 1;
	while (input[i] && nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			if ((return_value = pass_quotes(input, &i)))
				return (return_value);
		}
		else if (input[i] = '(')
			nbr_parenth++;
		else if (input[i] = ')')
			nbr_parenth--;
		i += (nbr_parenth) ? 1 : 0;
	}
	if (nbr_parenth ||i == 1)
		return ('(');
	*index += i;
	return (return_value = recursion_syntax(input + 1, i));
}

// check syntax error, return 0 if no error found, 1 if malloc error
// or the char if there is an error
// type : 0 WORD, 1 OPERATOR, 2 PARENTHESIS
char	syntax_error(char *input)
{
	int		i;
	int		type;
	char	return_value;

	i = 0;
	type = 1;
	while (input[i])
	{
		if (input[i] == ')')
			return (')');
		else if (input[i] == '(')
		{
			if ((return_value = syntax_parenth(input + i, type, &i)))
				return (return_value);
			type = 2;
		}
		i++;
	}
	return (0);
}