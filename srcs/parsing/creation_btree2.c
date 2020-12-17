/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_btree2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:12:10 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 18:21:09 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"
#include "parsing.h"
#include "libft_string.h"
#include "libft_mem.h"

void	init_oper(t_list **prev,
					t_list **prev_inverse, t_list **inverse)
{
	*prev = 0;
	*prev_inverse = 0;
	*inverse = 0;
}

int		cut_oper(t_list *inverse, t_list *prev_inverse, t_list **l_buffer)
{
	if (prev_inverse)
		prev_inverse->next = 0;
	*l_buffer = inverse;
	return (1);
}

/*
**find the operator || or && at the inverse and the operator is cutting the list
*/

int		find_operat2(char *operator1, char *operator2,
					t_list *current, t_list **l_buffer)
{
	t_list		*prev;
	t_list		*prev_inverse;
	t_list		*inverse;
	t_pretype	*c_pretype;

	init_oper(&prev, &prev_inverse, &inverse);
	while (current)
	{
		c_pretype = current->content;
		if (c_pretype->type == OPERAT &&
		(!ft_strcmp(operator1, (char *)c_pretype->content)
			|| !ft_strcmp(operator2, (char *)c_pretype->content)))
		{
			prev_inverse = prev;
			inverse = current;
		}
		prev = current;
		current = current->next;
	}
	if (inverse)
		return (cut_oper(inverse, prev_inverse, l_buffer));
	return (0);
}
