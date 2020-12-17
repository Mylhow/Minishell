/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:24:57 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 16:42:36 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		add_parenth(t_list **l_op_tok, char *input, int *index)
{
	int		start;
	int		i;
	t_list	*new_elem;
	char	*content;

	start = *index + 1;
	i = start;
	pass_parenth(&i, input);
	if (!(content = ft_strndup(input + start, i - start - 1)))
		return (0);
	if (!(new_elem = split_op_tok(content)))
		return (0);
	wrfree(content);
	if (!(add_pretype(l_op_tok, PARENTH, new_elem)))
		return (0);
	*index = i;
	return (1);
}

int		add_word(t_list **l_op_tok, char *input, int *index)
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

int		split_op_tok2(int *index, char *input, t_list **l_op_tok)
{
	int	i;

	i = *index;
	if (ft_memchr("|;", input[i], 3))
	{
		if (!add_single_operator(l_op_tok, input, &i))
			return (0);
		pass_blank(input, &i);
	}
	else if (input[i] == '(')
	{
		if (!add_parenth(l_op_tok, input, &i))
			return (0);
		pass_blank(input, &i);
	}
	else
	{
		if (!add_word(l_op_tok, input, &i))
			return (0);
	}
	*index = i;
	return (1);
}

t_list	*split_op_tok(char *input)
{
	int		i;
	t_list	*l_op_tok;

	i = 0;
	l_op_tok = 0;
	while (input[i])
	{
		pass_blank(input, &i);
		if (!ft_strncmp("&&", input + i, 2)
				|| !ft_strncmp("||", input + i, 2))
		{
			if (!add_double_operator(&l_op_tok, input, &i))
				return (0);
		}
		else
		{
			if (!split_op_tok2(&i, input, &l_op_tok))
				return (0);
		}
	}
	return (l_op_tok);
}
