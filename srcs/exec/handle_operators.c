/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:30:10 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 11:22:05 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"
#include "expander.h"
#include "exec.h"
#include "parsing.h"
#include "syntax_error.h"
#include "environement.h"
#include "signal_manager.h"

void	handle_sigquit(void)
{
	if (g_exit_status % 255 == 131 && g_piped != 1)
		ft_printf("Quit (core dumped)\n");
}

int		handle_operators2(char *type, t_btree *l_child, t_btree *r_child,
																int error)
{
	if (ft_strncmp(type, "&&", 2) == 0)
	{
		error += exec_tree(l_child);
		if (g_exit_status == 0)
		{
			error += exec_tree(r_child);
		}
	}
	else if (ft_strncmp(type, "||", 2) == 0)
	{
		error += exec_tree(l_child);
		if (g_exit_status != 0)
			error += exec_tree(r_child);
	}
	else if (ft_strncmp(type, "|", 1) == 0)
	{
		error += handle_pipes(l_child, r_child);
		handle_sigquit();
	}
	return (error);
}

int		handle_operators(char *type, t_btree *l_child, t_btree *r_child)
{
	int	error;

	error = 0;
	if (ft_strncmp(type, ";", 1) == 0)
	{
		error += exec_tree(l_child);
		error += exec_tree(r_child);
	}
	else
		error = handle_operators2(type, l_child, r_child, 0);
	return (error > 0 ? 1 : 0);
}
