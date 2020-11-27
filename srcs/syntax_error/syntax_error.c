/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:07:14 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/27 14:06:16 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_string.h"
#include "syntax_error.h"

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
	return_value = syntax_error(str_parenth);
	wrfree(str_parenth);
	return(return_value);
}

static char	syntax_parenth(char *input, int type, int *index)
{
	int		i;
	int		nbr_parenth;

	if (type == WORD)
		return (print_syntax_err());
	i = 1;
	nbr_parenth = 1;
	while (input[i] && nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NEW_LINE);
		}
		else if (input[i] == '(')
			nbr_parenth++;
		else if (input[i] == ')')
			nbr_parenth--;
		i += (nbr_parenth) ? 1 : 0;
	}
	if (nbr_parenth)
		return (NEW_LINE);
	*index += i + 1;
	return (recursion_parenth(input + 1, i));
}

char	check_end_line(char *input)
{
	int i;

	i = 0;
	while (input[i])
		i++;
	i--;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '>' || input[i] == '<')\
		return (print_syntax_err());
	else if (input[i] == '\\' || input[i] == '|')
		return (NEW_LINE);
	else if (i > 0 && (!ft_strncmp("&&", input + i - 1, 2)))
		return (NEW_LINE);
	return (TO_EXECUTE);
}

// check syntax
//  0 if it can be executed
//	1 if malloc error
//	2 if need to add a new line
//  3 if need to ask a new command
//
// type : 0 WORD, 1 OPERATOR, 2 PARENTHESIS
short	syntax_error(char *input)
{
	int		i;
	int		type;
	char	return_value;

	i = 0;
	type = OPERAT;
	if (check_empty_line(input))
		return (NEW_COMMAND);
	while (input[i])
	{
		if (input[i] == ')')
			return (print_syntax_err());
		else if (input[i] == '(')
		{
			if ((return_value = syntax_parenth(input + i, type, &i)))
				return (return_value);
			type = PARENTH;
		}
		else if (!ft_strncmp(">>", input + i, 2) || !ft_strncmp("&&", input + i, 2)
				|| !ft_strncmp("||", input + i, 2))
		{
			if (type == OPERAT)
				return (print_syntax_err());
			type = OPERAT;
			i += 2;
		}
		else if (ft_memchr("<>|;", input[i], 4))
		{
			if (type == OPERAT)
				return (print_syntax_err());
			type = OPERAT;
			i++;
		}
		else if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NEW_LINE);
			type = WORD;
			i++;
		}
		else if (ft_memchr(" \t\n", input[i], 3))
			pass_blank(input, &i);
		else
		{
			if (type == PARENTH)
				return (print_syntax_err());
			type = WORD;
			i++;
		}
	}
	return (check_end_line(input));
}