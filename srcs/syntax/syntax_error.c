/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:07:14 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/06 16:18:11 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "parsing.h"
char	recursion_parenth(char *input, int length)
{
	
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
			if ((return_value = pass_quotes(input + i, &i)))
				return (return_value);
		}
		else if (input[i] = '(')
			nbr_parenth++;
		else if (input[i] = ')')
			nbr_parenth--;
		i++;
	}
	if (nbr_parenth)
		return ('(');
	*index = i - 1;
	if (return_value = recursion_syntax(input, i - 1))
		return (return_value);
	return (0);
}

//check syntax error, return 0 if no error found or the char if there is an error
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
	}
	return (0);
}