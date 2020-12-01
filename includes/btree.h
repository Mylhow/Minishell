/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:08:41 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/27 17:11:02 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

typedef struct	s_btree
{
	int				type;
	char			*content;
	struct s_btree	*l_node;
	struct s_btree	*r_node;
}				t_btree;

t_btree		*new_node(int type, char *content)


#endif