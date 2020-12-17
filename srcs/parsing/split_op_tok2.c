/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op_tok2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:20:20 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 16:42:08 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pass_parenth(int *index, char *input)
{
	int		nbr_parenth;
	int		i;

	nbr_parenth = 1;
	i = *index;
	while (nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			pass_quotes(input, &i);
			i++;
		}
		if (input[i] == '(' || input[i] == ')')
			nbr_parenth += (input[i] == '(') ? 1 : -1;
		i++;
	}
	*index = i;
}

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
