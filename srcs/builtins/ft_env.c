/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:14:12 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 12:31:48 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_env(int ac, char **av, char **envp)
{
	int	i;

	(void)av;
	(void)envp;
	if (ac != 1)
	{
		ft_fprintf(2, "minishell: env: too many arguments.\n");
		return (1);
	}
	i = 0;
	while (g_envp && g_envp[i])
	{
		if (ft_strncmp(g_envp[i], "declare -x ", 11))
			ft_printf("%s\n", g_envp[i]);
		i++;
	}
	return (0);
}
