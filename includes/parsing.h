/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:19:58 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 18:22:52 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft_list.h"
# include "syntax_error.h"
# include "libft_list.h"
# include "libft_string.h"
# include "syntax_error.h"
# include "libft_mem.h"

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

t_list			*split_op_tok(char *input);
void			pass_parenth(int *index, char *input);
int				add_single_operator(t_list **l_op_tok, char *input, int *index);
int				add_double_operator(t_list **l_op_tok, char *input, int *index);

t_pretype		*create_pretype(int type, void *content);
int				add_pretype(t_list **l_op_tok, int type, void *content);

t_btree			*node_new(void *content);

int				creation_btree(t_list *list, t_btree **node);
int				find_operat2(char *operator1, char *operator2,
					t_list *current, t_list **l_buffer);
#endif
