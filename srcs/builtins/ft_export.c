/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:34:22 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/11 10:49:24 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_export(int ac, char **av, char **envp)
{
	char    **deconcat;
	int		i;
	int		invalid_id;

	(void)envp;
	if (ac == 1)
	{
		i = 0;
		while (g_envp && g_envp[i])
			ft_printf ("declare -x %s\n", g_envp[i++]);
		return (0);
	}
	else if (ac == 2)
	{
        if ((invalid_id = is_valid_var_name(av[1])) != 0)
		{
            ft_fprintf(STDERR_FILENO,
            "minishell: env: `%c': not a valid identifier.\n", av[1][invalid_id]);
			return (1);
		}
		if (!(deconcat = deconcat_var(av[1])))
			return (1);
		if (get_env(deconcat[0]) != NULL)
			set_var(deconcat[0], deconcat[1]);
		else
			add_var(deconcat[0], deconcat[1]);
		free(deconcat[0]);
        free(deconcat[1]);
        free(deconcat);
		return (0);
	}
	ft_fprintf(STDERR_FILENO, "minishell: export: too many arguments.\n");
	return (0);
}