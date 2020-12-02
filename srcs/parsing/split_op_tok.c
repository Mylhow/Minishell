/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:24:57 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/02 13:34:00 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"
#include "libft_string.h"
#include "syntax_error.h"
#include "libft_mem.h"
#include "parsing.h"

static int	add_single_operator(t_list **l_op_tok, char *input, int *index)
{
	char	*content;

	if (!(content = ft_strndup(input + *index, 1)))
		return (0);
	if (!(add_pretype(l_op_tok, OPERAT, content)))
		return (0);
	*index += 1;
	return (1);
}

static int	add_double_operator(t_list **l_op_tok, char *input, int *index)
{
	char	*content;

	if (!(content = ft_strndup(input + *index, 2)))
		return (0);
	if (!(add_pretype(l_op_tok, OPERAT, content)))
		return (0);
	*index += 2;
	return (1);
}

static int	add_word(t_list **l_op_tok, char *input, int *index)
{
	int		i;
	int		start;
	char	*content;

	i = *index;
	start = i;
	while (input[i] && !ft_memchr("|;", input[i], 2)
			&& ft_strncmp("&&", input + i, 2))
	{
		if (ft_memchr("\'\"", input[i], 2))
			pass_quotes(input, &i);
		i++;
	}
	if (!(content = ft_strndup(input + start, i - start)))
		return (0);
	if (!(add_pretype(l_op_tok, WORD, content)))
		return (0);
	*index = i;
	return (1);
}

static int	split_op_tok2(t_list **l_op_tok, char *input, int *i)
{
	if (ft_memchr("<>|;", input[*i], 5))
	{
		if (!add_single_operator(l_op_tok, input, i))
			return (0);
	}
	else if (input[*i] == '(')
	{
		if (!add_parenth(l_op_tok, input, i))
			return (0);
		pass_blank(input, i);
	}
	else
	{
		if (!add_word(l_op_tok, input, i))
			return (0);
	}
	return (1);
}

t_list		*split_op_tok(char *input)
{
	int		i;
	t_list	*l_op_tok;

	i = 0;
	l_op_tok = 0;
	while (input[i])
	{
		pass_blank(input, &i);
		if (!ft_strncmp(">>", input + i, 2) || !ft_strncmp("&&", input + i, 2)
				|| !ft_strncmp("||", input + i, 2))
		{
			if (!add_double_operator(&l_op_tok, input, &i))
				return (0);
		}
		else
		{
			if (!split_op_tok2(&l_op_tok, input, &i))
				return (0);
		}
	}
	return (l_op_tok);
}
