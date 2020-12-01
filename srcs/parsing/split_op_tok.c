/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:24:57 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/01 15:53:22 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"
#include "libft_string.h"
#include "syntax_error.h"
#include "libft_mem.h"
#include "parsing.h"


int		add_single_operator(t_list **l_op_tok, char *input, int *index)
{
	char	*content;

	if (!(content = ft_strndup(input + *index, 1)))
		return (0);
	if (!(add_pretype(l_op_tok, OPERAT, content)))
		return (0);
	*index += 1;
	return (1);
}

int		add_double_operator(t_list **l_op_tok, char *input, int *index)
{
	char	*content;

	if (!(content = ft_strndup(input + *index, 2)))
		return (0);
	if (!(add_pretype(l_op_tok, OPERAT, content)))
		return (0);
	*index += 2;
	return (1);
}

int		add_parenth(t_list	**l_op_tok, char *input, int *index)
{
	int		start;
	int		i;
	int		nbr_parenth;
	t_list	*new_elem;
	char	*content;

	start = *index + 1;
	i = start;
	nbr_parenth = 1;
	while (nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			pass_quotes(input, &i);
			i++;
		}
		if (input[i] == '(')
			nbr_parenth++;
		else if (input[i] == ')')
			nbr_parenth--;
		i++;
	}
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
	if(!(content = ft_strndup(input + start, i - start)))
		return (0);
	if (!(add_pretype(l_op_tok, WORD, content)))
		return (0);
	*index = i;
	return (1);
}

t_list	*split_op_tok(char *input)
{
	int	i;
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
		else if (ft_memchr("<>|;", input[i], 5))
		{
			if (!add_single_operator(&l_op_tok, input, &i))
				return (0);
		}
		else if (input[i] == '(')
		{
			if (!add_parenth(&l_op_tok, input, &i))
				return (0);
			pass_blank(input, &i);
		}
		else
		{
			if (!add_word(&l_op_tok, input, &i))
				return (0);
		}
	}
	return (l_op_tok);
}