/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op_tok2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:57:56 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/02 13:34:23 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"
#include "libft_string.h"
#include "syntax_error.h"
#include "libft_mem.h"
#include "parsing.h"

static void	end_parenth(char *input, int *i)
{
	int		nbr_parenth;

	nbr_parenth = 1;
	while (nbr_parenth)
	{
		if (ft_memchr("\'\"", input[*i], 2))
			pass_quotes(input, i);
		if (input[*i] == '(')
			nbr_parenth++;
		else if (input[*i] == ')')
			nbr_parenth--;
		(*i) += 1;
	}
}

int			add_parenth(t_list **l_op_tok, char *input, int *index)
{
	int		start;
	int		i;
	t_list	*new_elem;
	char	*content;

	start = *index + 1;
	i = start;
	end_parenth(input, &i);
	*index = i;
	if (!(content = ft_strndup(input + start, i - start - 1)))
		return (0);
	if (!(new_elem = split_op_tok(content)))
		return (0);
	wrfree(content);
	if (!(add_pretype(l_op_tok, PARENTH, new_elem)))
		return (0);
	return (1);
}
