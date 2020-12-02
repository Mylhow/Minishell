/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:19:58 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/02 13:36:15 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft_list.h"

//type = 0 operator, 1 simple word, 2 word into parenthesis
typedef struct	s_pretype
{
	int		type;
	void	*content;
}				t_pretype;

typedef struct	s_btree
{
	void			*content;
	struct s_btree	*l_child;
	struct s_btree	*r_child;
}				t_btree;


//SPLIT_OP_TOK_C
t_list	*split_op_tok(char *input);

//SPLIT_OP_TOK2_C
int		add_parenth(t_list **l_op_tok, char *input, int *index);

//PARSING_TOOLS_C
int			add_pretype(t_list **l_op_tok, int type, void *content);

//BTREE_TOOL_C
t_btree		*node_new(void *content);

//CREATION_BTREE_C
int		creation_btree(t_list *list, t_btree **node);
#endif