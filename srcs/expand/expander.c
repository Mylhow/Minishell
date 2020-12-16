/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:35:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 13:46:16 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	free_all(char **dst, char *simple_cmd)
{
	wrfree(dst);
	wrfree(simple_cmd);
}

/*
**	EXPAND_CMD
**	description: expands a simple command into a command struct
**
**	cmd: points to the destination of the expansion.
**	simple_command: the simple command string that needs to be expanded.
**
**	returns: 0 if everything has gone well, -1 if some expansion has failed.
**
**	ORDER OF EXPANSION :
**		- bash variables
**		- word splitting
**		- quote removal
**		- backslash removal
*/

int		expand_cmd(t_cmd **cmd, char *simple_command)
{
	char	**dst;

	dst = 0;
	if (!(dst = wrmalloc(sizeof(char *))))
		return (-1);
	if (expand_var(dst, simple_command) != 0)
	{
		free_all(dst, NULL);
		return (-1);
	}
	simple_command = *dst;
	if (expand_word(cmd, *dst) != 0)
	{
		free_all(dst, simple_command);
		return (-1);
	}
	free_all(dst, simple_command);
	expand_quotes(*cmd);
	expand_bslash(*cmd);
	return (0);
}
