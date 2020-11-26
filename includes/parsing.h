/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:19:58 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/16 17:03:38 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft_list.h"

//type = 0 operator, 1 simple word, 2 word into parenthesis
typedef struct	s_pretype
{
	int		type;
	char	*content;
}				t_pretype;


//SPLIT_OP_TOK_C
t_list	*split_operator(char *input);

//PARSING_TOOLS_C
int	add_pretype(t_list **l_op_tok, int type, char *content);

#endif