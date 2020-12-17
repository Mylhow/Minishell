/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:34:22 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/17 14:33:58 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		deconcat_free(char **str)
{
	wrfree(str[0]);
	wrfree(str[1]);
	wrfree(str);
}

static int		p_declared(void)
{
	int		i;
	char	**deconcat;

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
	return (0);
}

static int		update_var(char *var_name)
{
	char		**deconcat;

	if (!(deconcat = deconcat_var(var_name)))
		return (1);
	if (get_env(deconcat[0]) != NULL)
		set_var(deconcat[0], deconcat[1]);
	else
		add_var(deconcat[0], deconcat[1]);
	deconcat_free(deconcat);
	return (0);
}

int				ft_export(int ac, char **av, char **envp)
{
	int			i;
	int			error;

	error = 0;
	i = 1;
	(void)envp;
	if (ac == 1)
		return (p_declared());
	while (i < ac)
	{
		if (is_valid_var_name(av[i], ft_strlchr(av[i], '=')) != 0
		|| !ft_isalpha(av[i][0]))
		{
			ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier.\n", av[i++]);
			error = 1;
			continue;
		}
		if (update_var(av[i]) == 1)
			return (1);
		i++;
	}
	return (error);
}
