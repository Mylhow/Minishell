/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_btree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:00:15 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/09 16:35:57 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"
#include "parsing.h"
#include "libft_string.h"
#include "libft_mem.h"

t_btree		*node_new(void *content)
{
	t_btree	*new_node;

	if (!(new_node = wrmalloc(sizeof(t_btree))))
		return (0);
	new_node->content = content;
	new_node->l_child = 0;
	new_node->r_child = 0;
	return (new_node);
}

//find the operator and the operator is cutting the list
int		find_operat(char *operator1, char *operator2, t_list *t_op_tok, t_list **l_buffer)
{
	t_list		*prev;
	t_list		*current;
	t_pretype	*c_pretype;

	prev = 0;
	current = t_op_tok;
	while (current)
	{
		c_pretype = current->content;
		if (c_pretype->type == OPERAT && (!ft_strcmp(operator1, (char *)c_pretype->content)
			|| !ft_strcmp(operator2, (char *)c_pretype->content)))
		{
			if (prev)
				prev->next = 0;
			*l_buffer = current;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

//check if their is an operator
//find the priority operator and treat it
//return 0
t_list	*priority_operat(t_list *l_op_tok, t_list **l_left, t_list **l_right)
{
	t_list	*l_operator;

	if (find_operat(";", "", l_op_tok, &l_operator) || find_operat("&&", "||", l_op_tok, &l_operator) ||
		find_operat("|", "", l_op_tok, &l_operator))
	{
		*l_left = l_op_tok;
		*l_right = l_operator->next;
		return (l_operator);
	}
	return (0);
}


//return 0 if their is an operator
//return 1 if their is a malloc error
//return 2 if their is no operator
int		is_ope(t_list *l_op_tok, t_btree **node)
{
	t_list	*l_operator;
	t_list	*l_left;
	t_list	*l_right;

	l_left = 0;
	l_right = 0;
	l_operator = priority_operat(l_op_tok, &l_left, &l_right);
	if (!l_operator)
		return (2);
	if(!(*node = node_new(l_operator->content)))
		return (1);
	wrfree(l_operator);
	if ((creation_btree(l_left, &(*node)->l_child)))
		return (1);
	if ((creation_btree(l_right, &(*node)->r_child)))
		return(1);
	return (0);
}

//return 0 if everything go right
//return 1 if malloc error
int		creation_btree(t_list *list, t_btree **node)
{
	t_pretype	*pretype;
	int			return_value;

	if (!list)
		return (EXIT_SUCCESS);
	pretype = (t_pretype *)list->content;
	if((return_value = is_ope(list, node)) != 2)
		return (return_value);
	else if (pretype->type == WORD)
	{
		wrfree(list);
		if(!(*node = node_new(pretype)))
			return(EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (pretype->type == PARENTH)
	{
		wrfree(list);
		return (creation_btree(pretype->content, node));
	}
	return (EXIT_SUCCESS);
}