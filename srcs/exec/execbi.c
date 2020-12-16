/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:06:18 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 14:31:10 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	strplen(char **strp)
{
	int	i;

	i = 0;
	while (strp[i])
		i++;
	return (i);
}

int			execbi(char *name, char **argv)
{
	t_exec_builtin	exec;

	if (!(exec = is_builtin(name)))
		return (1);
	return (exec(strplen(argv), argv, g_envp));
}
