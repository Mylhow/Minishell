/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:34:22 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/11 15:31:12 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		p_declared(void)
{
	int	i;

	i = 0;
	while (g_envp && g_envp[i])
		ft_printf("declare -x %s\n", g_envp[i++]);
	return (0);
}

static void		deconcat_free(char **str)
{
	wrfree(str[0]);
	wrfree(str[1]);
	wrfree(str);
}

int				ft_export(int ac, char **av, char **envp)
{
	char	**deconcat;
	int		i;

	(void)envp;
	if (ac == 1)
		p_declared();
	else if (ac == 2)
	{
		if (is_valid_var_name(av[1], ft_strlchr(av[1], '=')) != 0)
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
	return (0);
}
