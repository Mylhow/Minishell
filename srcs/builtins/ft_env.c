/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:14:12 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/11 15:31:38 by lrobino          ###   ########.fr       */
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
		ft_printf("%s\n", g_envp[i++]);
	return (0);
}
