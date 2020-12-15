/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:34:22 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 14:19:53 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		deconcat_free(char **str)
{
	wrfree(str[0]);
	wrfree(str[1]);
	wrfree(str);
}

static void		p_declared(void)
{
	int	i;
	char **deconcat;

	i = 0;
	while (g_envp && g_envp[i])
	{
		deconcat = deconcat_var(g_envp[i]);
		if (!ft_strncmp("declare -x ", deconcat[0], 11))
			ft_printf("%s\n", deconcat[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", deconcat[0], deconcat[1]);
		deconcat_free(deconcat);
		i++;
	}
}

int				ft_export(int ac, char **av, char **envp)
{
	char		**deconcat;

	(void)envp;
	if (ac == 1)
	{
		p_declared();
		return (0);
	}
	else if (ac == 2)
	{
		if (is_valid_var_name(av[1], ft_strlchr(av[1], '=')) != 0
		|| !ft_isalpha(av[1][0]))
		{
			ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier.\n", av[1]);
			return (1);
		}
		if (!(deconcat = deconcat_var(av[1])))
			return (1);
		if (get_env(deconcat[0]) != NULL)
			set_var(deconcat[0], deconcat[1]);
		else
			add_var(deconcat[0], deconcat[1]);
		deconcat_free(deconcat);
		return (0);
	}
	ft_fprintf(STDERR_FILENO, "minishell: export: too many arguments.\n");
	return (1);
}
