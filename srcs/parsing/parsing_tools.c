/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:54:37 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/16 17:05:06 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"
#include "libft_mem.h"
#include "parsing.h"

//create a t_pretype and add it on the list
//return 1 if it works and 0 if malloc error
int	add_pretype(t_list **l_op_tok, int type, char *content)
{
	t_list		*new_elem;
	t_pretype	*new_pret;

	if (!(new_pret = wrmalloc(sizeof(t_pretype))))
		return (0);
	new_pret->type = type;
	new_pret->content = content;
	if (!(new_elem = ft_lstnew(new_pret)))
		return (0);
	ft_lstadd_back(l_op_tok, new_elem);
	return (1);
}